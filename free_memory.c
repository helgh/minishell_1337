/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:07:18 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/09/18 22:35:06 by mthamir          ###   ########.fr       */
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
