/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:43:11 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/09/18 22:34:00 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_lenlist(t_parse *data)
{
	t_env	*head;
	int		count;

	count = 0;
	head = data->envir;
	while (head)
	{
		count++;
		head = head->next;
	}
	return (count);
}

char	**l_list_to_array(t_parse *data)
{
	t_env	*head;
	char	**list;
	int		i;

	head = data->envir;
	i = -1;
	list = ft_malloc (sizeof(char *) * (ft_lenlist(data) + 1), data);
	while (head)
	{
		list[++i] = ft_strjoin(head->var, head->egal, data);
		list[i] = ft_strjoin(list[i], head->value, data);
		head = head->next;
	}
	list[++i] = NULL;
	return (list);
}
