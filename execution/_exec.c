/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exec.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:39:03 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/10/01 20:51:28 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	close_and_exit(t_parse *data, int *pipe_fd, int status)
{
	close_files(data);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	exit(status);
}

static void	execute_cmd(char **cmd, char *path, char **envp)
{
	if (execve(path, cmd, envp))
	{
		putstr_fd("M_H: ", 2);
		putstr_fd(cmd[0], 2);
		putstr_fd(": ", 2);
		perror("");
	}
	if (access(path, F_OK))
		exit (127);
	exit(126);
}

void	exec_builtins(t_parse *data, t_exec *ex)
{
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
	else if (!ft_strcmp(ex->cmd[0], "exit"))
		ft_exit(data, ex->cmd, ex);
}

static int	builtins(t_parse *data, t_exec *ex, int flag, int *pipe_fd)
{
	dup_input(ex);
	dup_output(ex, flag, pipe_fd);
	if (!check_red_fd(data, ex))
	{
		exec_builtins(data, ex);
		close_files(data);
		exit(data->exit_status);
	}
	exit(data->exit_status);
}

void	child_proccess(t_parse *data, t_exec *ex, int flag, int *pipe_fd)
{
	char	*path;

	ex->pid = fork();
	if (ex->pid < 0)
		return (print_error(data, F_FORK));
	if (!ex->pid)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		if (!ex->cmd[0] && !ex->files)
			return (close_and_exit(data, pipe_fd, 0));
		else if (!check_if_builtin(data, ex))
			builtins(data, ex, flag, pipe_fd);
		else if (!check_red_fd(data, ex))
		{
			path = check_access(data, ex);
			if (!path)
				return (close_and_exit(data, pipe_fd, 127));
			dup_input(ex);
			dup_output(ex, flag, pipe_fd);
			close_files(data);
			execute_cmd(ex->cmd, path, data->env);
		}
		close_and_exit(data, pipe_fd, 1);
	}
}
