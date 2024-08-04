/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:57:26 by mthamir           #+#    #+#             */
/*   Updated: 2023/12/02 12:04:13 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	check_start(const char *s, char d)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == d)
			return (0);
		i++;
	}
	return (1);
}

static	int	check_end(const char *l, char q)
{
	int	i;

	i = 0;
	while (l[i] != 0)
	{
		if (l[i] == q)
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strtrim(char const	*s1, char const	*set)
{
	int		i;
	int		count;
	char	*ret;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	i = 0;
	count = ft_strlen(s1);
	if (count == 0)
		return (ft_substr(s1, 0, 0));
	while (check_start(set, s1[i]) == 0)
		i++;
	if (i >= count)
		return (ft_substr(s1, 0, 0));
	while (check_end(set, s1[count - 1]) == 0)
		count--;
	ret = ft_substr(s1, i, (count - i));
	return (ret);
}
