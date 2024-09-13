/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 09:44:43 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/09/13 04:01:55 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cmd(char **cmd, char *path, char **envp)
{
	if (execve(path, cmd, envp))
		perror("M_H");
	exit(EXIT_FAILURE);
}

int	arg_env(t_parse *data, char **cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (ft_strcmp(cmd[i], "env"))
		{
			putstr_fd("env: ", 2);
			putstr_fd(cmd[i], 2);
			putstr_fd(": No such file or directory\n", 2);
			data->exit_status = 1;
			return (1);
		}
	}
	return (0);
}

int	check_if_builtin(t_parse *data, t_exec *ex)
{
	(void) data;
	if (!ft_strcmp(ex->cmd[0], "env"))
		return (0);
	else if (!ft_strcmp(ex->cmd[0], "export"))
		return (0);
	else if (!ft_strcmp(ex->cmd[0], "cd"))
		return (0);
	else if (!ft_strcmp(ex->cmd[0], "echo"))
		return (0);
	else if (!ft_strcmp(ex->cmd[0], "unset"))
		return (0);
	return (1);
}

void	exec_builtin(t_parse *data, t_exec *ex, int i, int *pipe_fd)
{
	int	std_out;

	std_out = dup(STDOUT_FILENO);
	if (i != 1)
		dup2(pipe_fd[0], 0);
	dup_output(ex, i, pipe_fd);
	if (!ft_strcmp(ex->cmd[0], "env"))
	{
		if (!arg_env(data, ex->cmd))
			data->exit_status = print_env(data);
	}
	else if (!ft_strcmp(ex->cmd[0], "export"))
		data->exit_status = _export(ex->cmd, data);
	else if (!ft_strcmp(ex->cmd[0], "cd"))
		data->exit_status = cd(ex->cmd, data);
	else if (!ft_strcmp(ex->cmd[0], "echo"))
		data->exit_status = ft_echo(ex->cmd);
	else if (!ft_strcmp(ex->cmd[0], "unset"))
		data->exit_status = _unset(ex->cmd, data);
	dup2(std_out, STDOUT_FILENO);
	close(std_out);
}

void	child_process(t_parse *data, t_exec *ex, int i, int *pipe_fd)
{
	int		pid;
	char	*path;

	path = check_access(data, ex);
	pid = fork();
	if (pid < 0)
		return ;
	else if (pid == 0)
	{
		if (!path)
			exit(127);
		dup_input(ex);
		dup_output(ex, i, pipe_fd);
		execute_cmd(ex->cmd, path, data->env);
	}
	else
	{
		close(pipe_fd[1]);
		if (i == 1)
		{
			waitpid(pid, &data->exit_status, 0);
			if (WIFEXITED(data->exit_status))
        		data->exit_status = WEXITSTATUS(data->exit_status);
			// else if (WIFSIGNALED(data->exit_status))
       		// 	data->exit_status = WTERMSIG(data->exit_status);
		}
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
	}
}

void	_exec(t_parse *data, t_exec *ex, int i)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (print_error(data, F_ALLOC));
	if (!check_if_builtin(data, ex))
		exec_builtin(data, ex, i, pipe_fd);
	else
		child_process(data, ex, i, pipe_fd);
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
	open_files(data, exec);
	std_in = dup(STDIN_FILENO);
	data->env = l_list_to_array(data);
	while (++i < data->nbr_cmd)
	{
		if (i == data->nbr_cmd - 1)
			flag = 1;
		if (!check_red_fd(data, ex, flag))
			_exec(data, ex, flag);
		ex = ex->next;
	}
	while (wait(NULL) != -1)
		;
	dup2(std_in, STDIN_FILENO);
	close (std_in);
}

t_exec	*parsing_part(char *str, t_parse *data_info)
{
	t_exec	*exec;

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
	if (!check_syntax_error(data_info))
		return (print_error(data_info, S_ERROR), NULL);
	exec = ready_for_exec(data_info);
	return (exec);
}

void	minishell(t_parse *data)
{
	t_exec		*exec;

	while (1)
	{
		signal_loop();
		data->cmd_info = NULL;
		data->r_line = readline("\033[0;31mM_H$\033[0m ");
		if (!data->r_line)
			return (free_and_exit(data));
		exec = parsing_part(data->r_line, data);
		if (exec)
			execution_part(data, exec);
		if (*data->r_line)
			add_history(data->r_line);
		free(data->r_line);
		free_all_memory(data->heap);
		data->heap = NULL;
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
		return (1);
	}
	data_info = init_struct(envp);
	if (!data_info)
		return (1);
	minishell(data_info);
}
