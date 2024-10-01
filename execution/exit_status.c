/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 01:55:17 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/10/01 21:51:25 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			data->exit_status = 127;
			return (1);
		}
	}
	return (0);
}

void	status(t_parse *data, int flag)
{
	unsigned char	c;

	while (wait(NULL) != -1)
		;
	if (flag)
		;
	else if (WIFSIGNALED(data->exit_status))
	{
		if (WTERMSIG(data->exit_status) == SIGINT)
			write(2, "\n", 1);
		else if (WTERMSIG(data->exit_status) == SIGQUIT)
			putstr_fd("Quit: 3\n", 2);
		data->exit_status = WTERMSIG(data->exit_status) + 128;
	}
	else
		data->exit_status = WEXITSTATUS(data->exit_status);
	c = data->exit_status;
	data->exit_status = c;
}
