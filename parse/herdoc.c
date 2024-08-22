/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:44:54 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/08/22 15:45:38 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*read_herdoc(t_parse *data, char *str, int flag)
{
	char	*line;
	char	*new_line;
	char	*herdoc;

	herdoc = ft_dup_str("", &data->heap);
	while (1)
	{
		line = readline("> ");
		if(!line)
			return (printf("%s", herdoc), NULL);
		if (!ft_strcmp(str, line))
			return (free(line), herdoc);
		new_line = ft_strjoin(line, "\n", &data->heap);
		free (line);
		if (*data->r_line)
			add_history(data->r_line);
		if (flag != 0)
			herdoc = ft_strjoin(herdoc, new_line, &data->heap);
		else
			herdoc = ft_strjoin(herdoc, set_value(data, new_line, &data->heap), &data->heap);
	}
	return (herdoc);
}

void	expand_herdoc(t_parse *data)
{
	t_cmd_info	*cmd;
	t_tokens	*tok;
	char		*type;
	char		*str;
	int			i;
	int			s;
	int			flag;

	i = -1;
	cmd = data->cmd_info;
	while (++i < data->nbr_cmd)
	{
		s = -1;
		tok = cmd->token;
		while (++s < cmd->nbr_token)
		{
			type = tok->type;
			str = tok->str;
			flag = tok->type_qoute;
			if (!ft_strcmp(type, "delim"))
				tok->str = read_herdoc(data, str, flag);
			tok = tok->next;
		}
		cmd = cmd->next;
	}
}
