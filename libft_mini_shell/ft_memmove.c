/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:38:16 by mthamir           #+#    #+#             */
/*   Updated: 2023/11/30 13:06:23 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dst_;
	unsigned char	*src_;
	size_t			i;

	dst_ = (unsigned char *)dst;
	src_ = (unsigned char *)src;
	i = 0;
	while (dst_ > src_ && len > 0)
	{
		dst_[len -1] = src_[len - 1];
		len--;
	}
	while (dst_ < src_ && i < len)
	{
		dst_[i] = src_[i];
		i++;
	}
	return ((void *)dst_);
}
