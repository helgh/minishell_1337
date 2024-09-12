/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_my_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 20:06:11 by mthamir           #+#    #+#             */
/*   Updated: 2024/09/11 21:32:46 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static char	*strcp(char *str, char *s, int i)
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

static char	**spl(const char *s, char c, char **str, int d, t_parse *data)
{
	str[d] = ft_malloc ((size(s, c, d) + 1) * sizeof(char), data);
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

char	**spl_msh(char *s, char c, t_parse *data)
{
	int		count;
	char	**str;
	int		d;
	int		i;

	d = 0;
	if (s == NULL)
		return (NULL);
	count = 2;
	str = ft_malloc ((count + 1) * sizeof (char *), data);
	if (str == NULL)
		return (NULL);
	while (d < count)
	{
		if (*s == c)
			s++;
		i = size(s, c, d);
		spl(s, c, str, d, data);
		strcp(str[d], s, i);
		s = s + i;
		d++;
	}
	str[d] = NULL;
	return (str);
}
