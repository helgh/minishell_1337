/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_dup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:11:49 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/08/18 17:43:22 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_dup_str(char *s1, t_leaks **heap)
{
	int		i;
	char	*str;

	i = ft_strlen(s1);
	str = ft_malloc((i + 1) * sizeof(char), heap);
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
