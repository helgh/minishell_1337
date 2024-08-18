/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spl_and_replace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:44:19 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/08/18 18:18:29 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	replace_value_within_quotes(char **str, int i, int *s)
{
	char	c;

	c = str[i][*s];
	while (str[i][++(*s)] && str[i][*s] != c)
	{
		if (str[i][*s] == -1)
			str[i][*s] = 124;
		else if (str[i][*s] == 32)
			str[i][*s] = -1;
	}
}

char	**split_and_replace(t_parse *data_info)
{
	int		i;
	int		s;

	i = -1;
	data_info->all_cmd = ft_split(data_info->line, 124, &data_info->heap);
	if (!data_info->all_cmd)
		return (free(data_info->line), NULL);
	data_info->nbr_cmd = 0;
	while (data_info->all_cmd[++i])
		data_info->nbr_cmd++;
	i = -1;
	while (data_info->all_cmd[++i])
	{
		s = -1;
		while (data_info->all_cmd[i][++s])
		{
			if (data_info->all_cmd[i][s] == '\'' || data_info->all_cmd[i][s] == '\"')
				replace_value_within_quotes(data_info->all_cmd, i, &s);
		}
	}
	return (data_info->all_cmd);
}
