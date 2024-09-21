/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 09:44:43 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/09/20 23:03:11 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_files(t_parse *data)
{
	int	i;

	i = -1;
	while (data->fd[++i] != -1)
		close (data->fd[i]);
}

void	execution_part(t_parse *data, t_exec *exec)
{
	t_exec	*ex;
	int		i;
	int		flag;
	int		std_in;

	i = -1;
	ex = exec;
	flag = 0;
	open_files(data, exec, 0);
	std_in = dup(STDIN_FILENO);
	data->env = l_list_to_array(data);
	data->pid = ft_malloc(sizeof(int) * data->nbr_cmd, data);
	while (++i < data->nbr_cmd)
	{
		if (i == data->nbr_cmd - 1)
			flag = 1;
		_exec(data, ex, flag);
		ex = ex->next;
	}
	status(data);
	close_files(data);
	dup2(std_in, STDIN_FILENO);
	close (std_in);
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
	if (!check_syntax_error(data_info, -1))
		return (print_error(data_info, S_ERROR), NULL);
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
			return (free_and_exit(data, 0));
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
