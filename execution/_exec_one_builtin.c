/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exec_one_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 01:50:32 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/09/30 19:42:31 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	else if (!ft_strcmp(ex->cmd[0], "pwd"))
		return (0);
	else if (!ft_strcmp(ex->cmd[0], "exit"))
		return (0);
	return (1);
}

static void	exec_one_builtin(t_parse *data, t_exec *ex)
{
	data->out = dup(STDOUT_FILENO);
	if (ex->red_out > 1 && ft_strcmp(ex->cmd[0], "exit"))
		dup2(ex->red_out, STDOUT_FILENO);
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
	if (ex->red_out > 1 && ft_strcmp(ex->cmd[0], "exit"))
		dup2(data->out, STDOUT_FILENO);
	close (data->out);
}

int	one_builtin(t_parse *data, t_exec *ex)
{
	if (!check_if_builtin(data, ex))
	{
		if (!check_red_fd(data, ex))
		{
			exec_one_builtin(data, ex);
			close_files(data);
		}
		else
			return (-1);
		return (0);
	}
	return (1);
}
