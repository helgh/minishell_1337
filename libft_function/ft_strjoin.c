/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 17:51:19 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/08/20 17:54:40 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	coppy(char *all, char const *s)
{
	int	i;

	i = 0;
	while (s[i] != 0)
	{
		all[i] = s[i];
		i++;
	}
	all[i] = 0;
}

char	*ft_strjoin(char *s1, char *s2, t_leaks **heap)
{
	int		i;
	int		s;
	char	*all;

	i = 0;
	s = 0;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 != NULL)
		i = ft_strlen(s1);
	if (s2 != NULL)
		s = ft_strlen(s2);
	all = ft_malloc(sizeof(char) * (i + s + 1), heap);
	if (all == NULL)
		return (NULL);
	if (s1 != NULL)
		coppy(all, s1);
	if (s2 != NULL)
		coppy((all + i), s2);
	return (all);
}
