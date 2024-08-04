/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:20:59 by mthamir           #+#    #+#             */
/*   Updated: 2023/11/22 18:54:19 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*ptr;
	unsigned char	d;

	ptr = (unsigned char *) b;
	d = (unsigned char)c;
	i = 0;
	while (len > i)
	{
		ptr[i] = d;
		i++;
	}
	return (ptr);
}
