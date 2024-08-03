/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:42:08 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/08/03 15:42:34 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_str(char const *str, char c)
{
	int	i;
	int	leng;

	i = 0;
	leng = 0;
	while (str[i] != 0)
	{
		while (str[i] == c && str[i] != 0)
			i++;
		if (str[i] != c && str[i] != 0)
			leng++;
		while (str[i] != c && str[i] != 0)
			i++;
	}
	return (leng);
}

static int	start(char const *str, char c)
{
	int	l;

	l = 0;
	while (str[l] != 0 && str[l] == c)
		l++;
	return (l);
}

static int	endstr(char const *str, char c)
{
	int	l;

	l = 0;
	while (str[l] != 0 && str[l] != c)
		l++;
	return (l);
}

static char	*coppy(char const *str, int l, char **all, int h)
{
	int		i;
	char	*s1;

	i = 0;
	s1 = (char *) malloc(sizeof(char) * l + 1);
	if (s1 == NULL)
	{
		while (h > 0)
		{
			h--;
			free (all[h]);
		}
		free (all);
		all = NULL;
		return (NULL);
	}
	while (i < l)
	{
		s1[i] = str[i];
		i++;
	}
	s1[i] = 0;
	return (s1);
}

char	**ft_split(char const *s, char c)
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
	len = count_str(s, c);
	all = (char **) malloc(sizeof(char *) * (len + 1));
	if (all == NULL)
		return (NULL);
	while (i < len)
	{
		size += start(s + size, c);
		end = endstr(s + size, c);
		all[i] = coppy(s + size, end, all, i);
		size += end;
		i++;
	}
	all[i] = NULL;
	return (all);
}
