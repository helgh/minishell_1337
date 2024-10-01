/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 23:45:14 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/10/01 21:50:12 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all_memory(t_leaks *heap)
{
	t_leaks	*tmp;

	while (heap && heap->next)
	{
		tmp = heap;
		heap = heap->next;
		if (tmp->adress)
		{
			free (tmp->adress);
			free (tmp->t_struct);
		}
	}
	if (heap)
	{
		free (heap->adress);
		free (heap->t_struct);
	}
}

void	free_and_exit(t_parse *data, unsigned char ex)
{
	if (data->heap)
		free_all_memory(data->heap);
	if (data->heap_env)
		free_all_memory(data->heap_env);
	if (data->r_line)
		free(data->r_line);
	if (data)
		free(data);
	exit(ex);
}

void	print_error(t_parse *data, int flag)
{
	if (flag == F_ALLOC)
	{
		putstr_fd("M_H: Failed allocation!\n", 2);
		free_and_exit(data, 1);
	}
	else if (flag == S_ERROR)
		putstr_fd("M_H: syntax error near unexpected token `newline'\n", 2);
	else if (flag == U_QOUTE)
		putstr_fd("Error: Unclosed qoutes!\n", 2);
	else if (flag == MAX_HER)
	{
		putstr_fd("M_H: maximum here-document count exceeded\n", 2);
		free_and_exit(data, 2);
	}
	else if (flag == F_PIPE)
	{
		putstr_fd("M_H: Failed to create a pipe\n", 2);
		free_and_exit(data, 1);
	}
	else if (flag == F_FORK)
	{
		putstr_fd("M_H: fork: ", 2);
		perror("");
		data->exit_status = 1;
	}
}
