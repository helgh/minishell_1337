/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_and_replace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:44:19 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/09/25 16:00:26 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_value(char **str, int i, int *s)
{
	char	c;

	c = str[i][*s];
	while (str[i][++(*s)] && str[i][*s] != c)
	{
		if (str[i][*s] == -1)
			str[i][*s] = 124;
		else if (str[i][*s] == 32)
			str[i][*s] = -1;
		else if (str[i][*s] == '\t')
			str[i][*s] = -2;
	}
}

char	**split_and_replace(t_parse *data)
{
	int		i;
	int		s;

	i = -1;
	data->all_cmd = ft_split(data->line, 124, 124, data);
	data->nbr_cmd = 0;
	while (data->all_cmd[++i])
		data->nbr_cmd++;
	i = -1;
	while (data->all_cmd[++i])
	{
		s = -1;
		while (data->all_cmd[i][++s])
		{
			if (data->all_cmd[i][s] == '\'' || data->all_cmd[i][s] == '\"')
				replace_value(data->all_cmd, i, &s);
		}
	}
	return (data->all_cmd);
}
