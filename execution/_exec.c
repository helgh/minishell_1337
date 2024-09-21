/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exec.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 01:50:32 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/09/21 22:07:31 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	execute_cmd(char **cmd, char *path, char **envp)
{
	if (execve(path, cmd, envp))
	{
		putstr_fd("M_H: ", 2);
		putstr_fd(cmd[0], 2);
		putstr_fd(": ", 2);
		perror("");
	}
	exit(127);
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
	else if (!ft_strcmp(ex->cmd[0], "exit"))
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
	else if (!ft_strcmp(ex->cmd[0], "exit"))
		ft_exit(data, ex->cmd, ex);
	dup2(std_out, STDOUT_FILENO);
	close(std_out);
}

static void	child_proccess(t_parse *data, t_exec *ex, int i, int *pipe_fd)
{
	char	*path;

	data->pid[ex->pos] = fork();
	if (data->pid[ex->pos] < 0)
		print_error(data, F_FORK);
	else if (data->pid[ex->pos] == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		if (!ex->cmd[0] && !ex->files)
			exit(0);
		if (!check_red_fd(data, ex, i))
		{
			path = check_access(data, ex);
			if (!path)
				return (close_files(data), exit(127));
			dup_input(ex);
			dup_output(ex, i, pipe_fd);
			close_files(data);
			execute_cmd(ex->cmd, path, data->env);
		}
		else
			return (close_files(data), exit(1));
	}
}

void	_exec(t_parse *data, t_exec *ex, int i)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (print_error(data, F_PIPE));
	if (!check_if_builtin(data, ex))
	{
		if (!check_red_fd(data, ex, i))
			exec_builtin(data, ex, i, pipe_fd);
		else
		{
			close(pipe_fd[1]);
			close(pipe_fd[0]);
		}
	}
	else
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		child_proccess(data, ex, i, pipe_fd);
		close(pipe_fd[1]);
		waitpid(data->pid[data->nbr_cmd - 1], &data->exit_status, 0);
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
	}
}
