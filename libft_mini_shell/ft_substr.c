/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 19:15:42 by mthamir           #+#    #+#             */
/*   Updated: 2023/11/29 13:05:57 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*err1(void)
{
	char	*str;

	str = (char *) malloc (1 * sizeof(char));
	if (!str)
		return (NULL);
	*str = '\0';
	return (str);
}

static	char	*err2(const char *s, size_t i, unsigned int start)
{
	char	*str;
	size_t	k;
	size_t	l;

	k = 0;
	l = i - start;
	str = (char *) malloc ((l + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (k < i && s[start] != '\0')
	{
		str[k] = s[start];
		k++;
		start++;
	}
	str[k] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	char	*d;
	size_t	i;
	size_t	k;

	if (s == NULL)
		return (NULL);
	d = (char *)s;
	k = 0;
	i = ft_strlen(s);
	if (start > i)
		return (err1());
	if (len > (i - start))
		return (err2(s, i, start));
	str = (char *) malloc ((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (k < len && start < i && d[start] != '\0')
	{
		str[k] = d[start];
		k++;
		start++;
	}
	str[k] = '\0';
	return (str);
}
