/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exec.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 01:50:32 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/09/16 01:54:44 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	execute_cmd(char **cmd, char *path, char **envp)
{
	if (execve(path, cmd, envp))
		perror("M_H");
	exit(EXIT_FAILURE);
}

static int	check_if_builtin(t_parse *data, t_exec *ex)
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
	else if (!ft_strcmp(ex->cmd[0], "pwd"))
		return (0);
	return (1);
}

static void	exec_builtin(t_parse *data, t_exec *ex, int i, int *pipe_fd)
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
	else if (!ft_strcmp(ex->cmd[0], "pwd"))
		data->exit_status = get_pwd();
	dup2(std_out, STDOUT_FILENO);
	close(std_out);
}

static void	child_process(t_parse *data, t_exec *ex, int i, int *pipe_fd)
{
	int		pid;
	char	*path;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	path = check_access(data, ex);
	pid = fork();
	if (pid < 0)
		return ;
	else if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		if (!path)
			exit(127);
		dup_input(ex);
		dup_output(ex, i, pipe_fd);
		execute_cmd(ex->cmd, path, data->env);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
	}
}

void	_exec(t_parse *data, t_exec *ex, int i, int len)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (print_error(data, F_ALLOC));
	if (!ft_strcmp(ex->cmd[0], "exit"))
		ft_exit(data, ex->cmd, ex, len);
	else if (!check_if_builtin(data, ex))
		exec_builtin(data, ex, i, pipe_fd);
	else
		child_process(data, ex, i, pipe_fd);
}
