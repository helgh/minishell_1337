/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_my_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 20:06:11 by mthamir           #+#    #+#             */
/*   Updated: 2024/08/18 13:32:58 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/* my split function to use it for envirment and  export */


static int	size(const char *s, char c, int d)
{
	int	j;

	j = 0;
	if (d == 0)
	{
		while (s[j] != c && s[j] != '\0')
			j++;
	}
	else
		while(s[j])
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
	str[d] = (char *) malloc ((size(s, c, d) + 1) * sizeof(char));
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

char	**spl_msh(char const *s, char c)
{
	int		count;
	char	**str;
	int		d;
	int		i;

	d = 0;
	if (s == NULL)
		return (NULL);
	count = 2;
	str = (char **) malloc ((count + 1) * sizeof (char *));
	if (str == NULL)
		return (NULL);
	while (d < count)
	{
		if (*s == c)
			s++;
		i = size(s, c, d);
		spl(s, c, str, d);
		strcp(str[d], s, i);
		s = s + i;
		d++;
	}
	str[d] = NULL;
	return (str);
}