/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 20:10:46 by mthamir           #+#    #+#             */
/*   Updated: 2023/12/01 13:27:49 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dsl;
	size_t	srl;
	size_t	i;

	if (dst == NULL && dstsize == 0)
		return (ft_strlen(src));
	srl = ft_strlen(src);
	dsl = ft_strlen(dst);
	i = 0;
	if (dstsize < dsl + 1)
		return (dstsize + srl);
	if (dstsize > dsl + 1)
	{
		while (src[i] != '\0' && dsl + i < dstsize - 1)
		{
			dst[dsl + i] = src[i];
			i++;
		}
	}
	dst[dsl + i] = '\0';
	return (dsl + srl);
}
