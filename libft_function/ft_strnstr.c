/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 23:47:42 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/09/12 23:47:57 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;
	char	*tofind;

	i = 0;
	str = (char *) haystack;
	tofind = (char *) needle;
	if (tofind[i] == 0)
		return (str);
	while (i < len && str[i] != 0)
	{
		j = 0;
		while (str[i + j] == tofind[j] && (i + j) < len)
		{
			if (tofind[j + 1] == 0)
				return (str + i);
			j++;
		}
		i++;
	}
	return (0);
}
