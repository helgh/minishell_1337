/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strncmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:16:04 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/08/31 22:32:13 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s10;
	unsigned char	*s20;

	i = 0;
	s10 = (unsigned char *)s1;
	s20 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (i < n && (s10[i] != 0 || s20[i] != 0))
	{
		if (s10[i] > s20[i])
			return (s10[i] - s20[i]);
		if (s10[i] < s20[i])
			return (s10[i] - s20[i]);
		i++;
	}
	if (s20[i])
		return (1);
	return (0);
}
