/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_herdoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:20:13 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/08/23 15:37:40 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_restore_input(void)
{
	open("/dev/tty", O_RDONLY);
	signal(SIGINT, signal_handler);
}

void	handler(int sig)
{
	(void) sig;
	close (0);
}

void	signal_herdoc(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}
