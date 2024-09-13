/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 00:22:38 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/09/13 00:26:14 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dup_input(t_exec *ex)
{
	if (ex->red_herdoc)
		dup2(ex->red_herdoc, 0);
	else if (ex->red_in)
		dup2(ex->red_in, 0);
}

void	dup_output(t_exec *ex, int i, int *pipe_fd)
{
	close(pipe_fd[0]);
	if (ex->red_out == 1 && i == 0)
		dup2(pipe_fd[1], STDOUT_FILENO);
	else
		dup2(ex->red_out, STDOUT_FILENO);
	close(pipe_fd[1]);
}
