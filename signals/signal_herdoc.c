/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_herdoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:20:13 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/08/22 15:51:33 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_restore_input(void)
{
	open("/dev/tty", O_RDONLY);
}

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		close (0);
		global_v = 1;
	}
}

void	signal_herdoc(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}
