/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:50:17 by mthamir           #+#    #+#             */
/*   Updated: 2023/12/01 14:45:19 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void*))
{
	t_list	*node;
	t_list	*ret;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	node = ft_lstnew(f(lst->content));
	ret = node;
	lst = lst->next;
	while (lst != NULL)
	{
		if (node == NULL)
			ft_lstclear(&ret, del);
		ft_lstadd_back(&node, ft_lstnew(f(lst->content)));
		lst = lst->next;
	}
	return (ret);
}
