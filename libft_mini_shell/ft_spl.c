/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 22:24:39 by mthamir           #+#    #+#             */
/*   Updated: 2024/08/15 05:48:16 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	c_arr(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
			count++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count);
}

static int	size(const char *s, char c)
{
	int	j;

	j = 0;
	while (s[j] != c && s[j] != '\0')
		j++;
	return (j);
}

static char	*strcp(char *str, const char	*s, int i)
{
	int	c;

	c = 0;
	while (c < i)
	{
		str[c] = s[c];
		c++;
	}
	str[c] = '\0';
	return (str);
}

static char	**spl(const char *s, char c, char **str, int d)
{
	str[d] = (char *) malloc ((size(s, c) + 1) * sizeof(char));
	if (str[d] == NULL)
	{
		while (d > 0)
		{
			d--;
			free(str[d]);
		}
		free(str);
		return (NULL);
	}
	return (str);
}

char	**ft_spl(char const *s, char c)
{
	int		count;
	char	**str;
	int		d;
	int		i;

	d = 0;
	if (s == NULL)
		return (NULL);
	count = c_arr(s, c);
	str = (char **) malloc ((count + 1) * sizeof (char *));
	if (str == NULL)
		return (NULL);
	while (d < count)
	{
		while (*s == c)
			s++;
		i = size(s, c);
		spl(s, c, str, d);
		strcp(str[d], s, i);
		s = s + i;
		d++;
	}
	str[d] = NULL;
	return (str);
}
