/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:07:18 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/08/29 03:37:29 by hael-ghd         ###   ########.fr       */
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
