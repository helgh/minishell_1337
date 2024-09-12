/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:12:35 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/09/11 21:09:34 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_str(char const *str, char c, char c1)
{
	int	i;
	int	leng;

	i = 0;
	leng = 0;
	while (str[i] != 0)
	{
		while (str[i] && (str[i] == c || str[i] == c1))
			i++;
		if (str[i] && str[i] != c && str[i] != c1)
			leng++;
		while (str[i] && str[i] != c && str[i] != c1)
			i++;
	}
	return (leng);
}

static int	start(char const *str, char c, char c1)
{
	int	l;

	l = 0;
	while (str[l] && (str[l] == c || str[l] == c1))
		l++;
	return (l);
}

static int	endstr(char const *str, char c, char c1)
{
	int	l;

	l = 0;
	while (str[l] && str[l] != c && str[l] != c1)
		l++;
	return (l);
}

static char	*coppy(char const *str, int l, t_parse *data)
{
	int		i;
	char	*s1;

	i = 0;
	s1 = ft_malloc(sizeof(char) * (l + 1), data);
	if (s1 == NULL)
		return (NULL);
	while (i < l)
	{
		s1[i] = str[i];
		i++;
	}
	s1[i] = 0;
	return (s1);
}

char	**ft_split(char const *s, char c, char c1, t_parse *data)
{
	int		i;
	char	**all;
	int		end;
	int		size;
	int		len;

	size = 0;
	i = 0;
	if (s == NULL)
		return (NULL);
	len = count_str(s, c, c1);
	all = ft_malloc(sizeof(char *) * (len + 1), data);
	if (all == NULL)
		return (NULL);
	while (i < len)
	{
		size += start(s + size, c, c1);
		end = endstr(s + size, c, c1);
		all[i] = coppy(s + size, end, data);
		size += end;
		i++;
	}
	all[i] = NULL;
	return (all);
}
