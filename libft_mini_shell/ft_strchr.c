/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:51:04 by mthamir           #+#    #+#             */
/*   Updated: 2023/12/01 13:38:10 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	r;
	int		i;
	char	*re;

	i = 0;
	r = (char)c;
	re = (char *)s;
	while (re[i] != r)
	{
		if (re[i] == '\0')
			return (NULL);
		i++;
	}
	return (re + i);
}
