/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 20:59:53 by mthamir           #+#    #+#             */
/*   Updated: 2023/12/01 13:37:29 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	o;
	int		i;
	char	*str;

	o = (char)c;
	str = (char *)s;
	i = 0;
	if (str[i] == 0 && o == 0)
		return (str);
	while (str[i] != 0)
		i++;
	while (i >= 0)
	{
		if (str[i] == o)
			return (str + i);
		i--;
	}
	return (NULL);
}
