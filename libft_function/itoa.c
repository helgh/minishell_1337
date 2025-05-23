/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:10:43 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/09/11 21:15:34 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*i_to_a(int n, t_parse *data)
{
	int		i;
	int		c;
	char	*str;
	char	*d;

	i = 0;
	c = count_case(n, i);
	str = ft_malloc ((c + 1) * sizeof(char), data);
	d = dd(str, c, n);
	return (d);
}
