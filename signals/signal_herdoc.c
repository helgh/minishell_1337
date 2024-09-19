/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_herdoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:20:13 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/09/19 02:53:07 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_restore_input(t_parse *data)
{
	if (open("/dev/tty", O_RDONLY) == -1)
	{
		perror("");
		free_and_exit(data, 1);
	}
	signal(SIGINT, signal_handler);
}

void	handler(int sig)
{
	(void) sig;
	close (0);
	g_int = 1;
}

void	signal_herdoc(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}
