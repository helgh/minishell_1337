/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:14:00 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/09/18 06:40:03 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_handler(int sig)
{
	(void) sig;
	printf("\n");
	g_int = 1;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_loop(t_parse *data)
{
	(void) data;
	rl_catch_signals = 0;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
