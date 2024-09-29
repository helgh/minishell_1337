/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exec.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 01:50:32 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/09/29 22:14:13 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void f()
{
	system("lsof -c minishell");
}
void	close_and_exit(t_parse *data, int *pipe_fd, int status)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close_files(data);
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
}

void	child_proccess(t_parse *data, t_exec *ex, int i, int *pipe_fd)
{
	char	*path;

	ex->pid = fork();
	if (ex->pid < 0)
		print_error(data, F_FORK);
	if (ex->pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		if (!ex->cmd[0] && !ex->files)
			return (close_and_exit(data, pipe_fd, 0));
		if (!builtins(data, ex, &i, pipe_fd))
			return (close_and_exit(data, pipe_fd, data->exit_status));
		else if (!check_red_fd(data, ex, i))
		{
			path = check_access(data, ex);
			if (!path)
				return (close_and_exit(data, pipe_fd, 127));
			dup_input(ex);
			dup_output(ex, i, pipe_fd);
			close_files(data);
			execute_cmd(ex->cmd, path, data->env);
		}
		close_and_exit(data, pipe_fd, 1);
	}
}


int	builtins(t_parse *data, t_exec *ex, int *flag, int *pipe_fd)
{
	int	std_out;

	if (ex->pos == data->nbr_cmd - 1)
		*flag = 1;
	if (*flag)
		std_out = dup(STDOUT_FILENO);
	if (!check_if_builtin(data, ex))
	{
		if (!check_red_fd(data, ex, *flag))
			exec_builtin(data, ex, *flag, pipe_fd);
		else
		{
			close(pipe_fd[1]);
			close(pipe_fd[0]);
		}
		if (*flag)
		{
			dup2(std_out, STDOUT_FILENO);
			close(std_out);
		}
		return (0);
	}
	return (1);
}
