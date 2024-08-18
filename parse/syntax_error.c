/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:56:36 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/08/18 18:19:05 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_only_space_and_tab(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] != 32 && str[i] != 9)
			return (1);
	return (0);
}

int	check_if_operator(char *type)
{
	if (!ft_strcmp(type, "red_in"))
		return (0);
	else if (!ft_strcmp(type, "red_out"))
		return (0);
	else if (!ft_strcmp(type, "append"))
		return (0);
	else if (!ft_strcmp(type, "herdoc"))
		return (0);
	return (1);
}

int	check_syntax_error(t_parse *data)
{
	int			i;
	int			s;
	t_tokens	*tmp;
	t_cmd_info	*cmd;
	int			flag;

	i = -1;
	tmp = data->token;
	cmd = data->cmd_info;
	while (++i < data->nbr_cmd)
	{
		s = -1;
		flag = 0;
		while (++s < cmd->nbr_token)
		{
			if ((s + 1) == cmd->nbr_token && check_if_operator(tmp->type) == 0)
				return (0);
			else if (check_if_operator(tmp->type) == 0 && check_if_operator(tmp->next->type) == 0)
				return (0);
			flag = 1;
			tmp = tmp->next;
		}
		if (flag == 0)
			return (0);
		cmd = cmd->next;
	}
	return (1);
}
