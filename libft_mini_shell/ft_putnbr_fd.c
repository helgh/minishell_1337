/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:02:57 by mthamir           #+#    #+#             */
/*   Updated: 2023/11/29 15:36:33 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	c;

	c = n;
	if (fd >= 0)
	{
		if (c < 0)
		{
			ft_putchar_fd('-', fd);
			c = c * -1; 
		}
		if (c < 10)
			ft_putchar_fd(c + '0', fd);
		if (c > 9)
		{
			ft_putnbr_fd((c / 10), fd);
			ft_putchar_fd((c % 10) + '0', fd);
		}
	}
}
