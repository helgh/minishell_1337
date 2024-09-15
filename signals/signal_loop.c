/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:14:00 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/09/14 22:18:07 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_handler(int sig)
{
	(void) sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_loop(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
