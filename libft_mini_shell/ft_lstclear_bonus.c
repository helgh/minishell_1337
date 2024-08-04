/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 19:06:46 by mthamir           #+#    #+#             */
/*   Updated: 2023/12/01 14:32:10 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*node;
	t_list	*aux;

	if (lst == NULL || del == NULL)
		return ;
	node = *lst;
	if (node != NULL)
	{
		while (node != NULL)
		{
			aux = node;
			node = node->next;
			del(aux->content);
			free(aux);
		}
		*lst = NULL;
	}
}
