/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 09:44:43 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/10/01 21:55:40 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_exec(t_parse *data, t_exec *ex, int *pipe_fd)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while (++i < data->nbr_cmd)
	{
		if (pipe(pipe_fd) == -1)
			return (print_error(data, F_PIPE), 1);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		if (i == data->nbr_cmd - 1)
			flag = 1;
		child_proccess(data, ex, flag, pipe_fd);
		close(pipe_fd[1]);
		if (ex->pos == data->nbr_cmd - 1)
			waitpid(ex->pid, &data->exit_status, 0);
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
		if (ex->pid < 0)
			return (1);
		ex = ex->next;
	}
	return (0);
}

void	execution_part(t_parse *data, t_exec *exec)
{
	t_exec	*ex;
	int		pipe_fd[2];
	int		flag;

	ex = exec;
	open_files(data, exec, 0);
	data->env = l_list_to_array(data);
	if (data->nbr_cmd == 1 && !one_builtin(data, exec))
		;
	else
	{
		data->in = dup(STDIN_FILENO);
		flag = _exec(data, ex, pipe_fd);
		status(data, flag);
		dup2(data->in, STDIN_FILENO);
		close_files(data);
		close (data->in);
	}
}

t_exec	*parsing_part(char *str, t_parse *data_info)
{
	t_exec	*exec;

	exec = NULL;
	if (!check_if_only_space_and_tab(str))
		return (NULL);
	if (!check_qoutes(str, length_line(str), data_info))
		return (NULL);
	if (!split_and_replace(data_info))
		return (NULL);
	if (!cmd_info_struct(data_info))
		return (NULL);
	expantion(data_info);
	checker_herdoc(data_info);
	if (max_herdoc(data_info))
		return (print_error(data_info, MAX_HER), NULL);
	expand_herdoc(data_info);
	if (data_info->r_line[0] == '&' || !check_syntax_error(data_info, -1))
	{
		data_info->exit_status = 258;
		return (print_error(data_info, S_ERROR), NULL);
	}
	if (!g_int)
		exec = ready_for_exec(data_info);
	return (exec);
}

void	minishell(t_parse *data)
{
	t_exec			*exec;
	struct termios	attr;

	while (1)
	{
		signal_loop(data);
		data->cmd_info = NULL;
		data->r_line = readline("\001\033[0;31m\002M_H$\001\033[0m\002 ");
		if (g_int)
			data->exit_status = 1;
		if (!data->r_line)
			return (free_and_exit(data, data->exit_status));
		g_int = 0;
		exec = parsing_part(data->r_line, data);
		tcgetattr(STDIN_FILENO, &attr);
		if (*data->r_line)
			add_history(data->r_line);
		if (exec)
			execution_part(data, exec);
		free(data->r_line);
		free_all_memory(data->heap);
		data->heap = NULL;
		tcsetattr(STDIN_FILENO, TCSANOW, &attr);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_parse	*data_info;

	(void) av;
	if (ac != 1)
	{
		putstr_fd("M_H: ", 2);
		putstr_fd(av[1], 2);
		putstr_fd(": No such file or directory\n", 2);
		return (127);
	}
	data_info = init_struct(envp);
	if (!data_info)
		return (1);
	increment_shlvl(data_info);
	minishell(data_info);
	return (0);
}
