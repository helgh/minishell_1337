/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:13:27 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/09/11 21:16:31 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*join_str(t_parse *data, char *str, char *s, int l)
{
	int		i;
	int		len;
	char	*join;
	int		n;

	i = l;
	while (str[++i] && (ft_isalnum(str[i]) || str[i] == 95))
		;
	len = ft_strlen(s) + (ft_strlen(str) - (i - l));
	join = ft_malloc(len + 1, data);
	n = -1;
	while (++n < l)
		join[n] = str[n];
	while (s && *s)
		join[n++] = *(s++);
	while (i < ft_strlen(str))
		join[n++] = str[i++];
	join[n] = 0;
	return (join);
}
