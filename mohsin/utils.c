/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 20:07:34 by mthamir           #+#    #+#             */
/*   Updated: 2024/08/13 20:35:12 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

/*ft_strlen function*/

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*s != 0)
	{
		s++;
		i++;
	}
	return (i);
}


/*ft_strdup function */

char	*ft_strdup(const char	*s1)
{
	int		i;
	char	*str;

	i = ft_strlen(s1);
	str = (char *) malloc ((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

/*ft_strjoin function */

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*str;
	char	*ret;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	i = ft_strlen(s1) +ft_strlen(s2);
	str = (char *) malloc ((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ret = str;
	while (*s1 != '\0')
		*str++ = *s1++;
	while (*s2 != '\0')
		*str++ = *s2++;
	*str = '\0';
	return (ret);
}

/*ft_strcmp helpful function */

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*d1;
	unsigned char	*d2;

	d1 = (unsigned char *)s1;
	d2 = (unsigned char *)s2;
	i = 0;
	while (d1[i])
	{
		if (d1[i] != d2[i])
			return (d1[i] - d2[i]);
		i++;
	}
	return (0);
}