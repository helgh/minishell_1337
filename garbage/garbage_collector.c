/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:38:52 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/08/22 16:40:24 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_leaks	*leaks_collector(void *for_leaks, t_leaks **heap)
{
	t_leaks	*tmp;
	t_leaks	*new;

	tmp = *heap;
	new = malloc(sizeof(t_leaks));
	if (!new)
		return (free_all_memory(*heap), NULL);
	new->adress = for_leaks;
	new->t_struct = new;
	new->next = NULL;
	if (!*heap)
		return (*heap = new);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (*heap);
}

void	*ft_malloc(size_t size, t_leaks **heap)
{
	char	*new;

	new = malloc (size);
	if (!new)
		return (free_all_memory(*heap), NULL);
	if (!leaks_collector(new, heap))
		print_error(F_ALLOC, NULL);
	return (new);
}
