/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:35:03 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/09/11 22:36:12 by hael-ghd         ###   ########.fr       */
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

char	*ft_strjoin_env(char *s1, char *s2, t_parse *data)
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
	all = ft_env_malloc(sizeof(char) * (i + s + 1), data);
	if (s1 != NULL)
		coppy(all, s1);
	if (s2 != NULL)
		coppy((all + i), s2);
	return (all);
}
