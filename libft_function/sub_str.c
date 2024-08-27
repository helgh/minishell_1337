/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 01:31:57 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/08/27 02:18:13 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*sub_str(char *s, unsigned int start, size_t len, t_leaks **heap)
{
	size_t			i;
	unsigned int	l;
	char			*new;

	i = 0;
	new = NULL;
	if (s == NULL)
		return (NULL);
	l = ft_strlen(s);
	if (start > l || len == 0)
		new = (char *) ft_malloc(sizeof(char) * 1, heap);
	else if ((l - start) < len)
		new = (char *) ft_malloc(sizeof(char) * ((l - start) + 1), heap);
	else
		new = (char *) ft_malloc(sizeof(char) * (len + 1), heap);
	if (new == NULL)
		return (NULL);
	while (i < len && start < l)
		new[i++] = s[start++];
	new[i] = 0;
	return (new);
}
