/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:28:48 by mthamir           #+#    #+#             */
/*   Updated: 2023/11/30 11:29:40 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	count_case(int nb, int i)
{
	long int	d;

	d = nb;
	if (d == 0)
		return (1);
	if (d < 0)
	{
		d = -d;
		i++;
	}
	while (d > 0)
	{
		d = d / 10;
		i++;
	}
	return (i);
}

static char	*dd(char *str, int c, int n)
{
	long int	k;

	k = n;
	str[c] = '\0';
	c--;
	if (k < 0)
	{
		str[0] = '-';
		k = -k;
	}
	if (k == 0)
		str[c] = 48;
	while (k > 0)
	{
		str[c] = (k % 10) + 48;
		c--;
		k = k / 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	int		i;
	int		c;
	char	*str;
	char	*d;

	i = 0;
	c = count_case(n, i);
	str = (char *) malloc ((c + 1) * sizeof(char));
	if (!str)
		return (NULL);
	d = dd(str, c, n);
	return (d);
}
