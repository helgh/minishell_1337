/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_herdoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:20:13 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/09/19 00:33:51 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handler_herdoc(int sig)
{
	(void) sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_restore_input(void)
{
	open("/dev/tty", O_RDONLY);
	signal(SIGINT, handler_herdoc);
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
