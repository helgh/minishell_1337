/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:15:42 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/09/13 03:46:21 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*d1;
	unsigned char	*d2;

	d1 = (unsigned char *)s1;
	d2 = (unsigned char *)s2;
	i = 0;
	if (!s1 || !s2)
		return (1);
	while (d1[i] || d2[i])
	{
		if (d1[i] != d2[i])
			return (d1[i] - d2[i]);
		i++;
	}
	return (0);
}
