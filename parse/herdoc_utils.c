/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:34:56 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/09/18 22:57:48 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_to_next(t_exec **lst, t_exec *new)
{
	t_exec	*ptr;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	ptr = *lst;
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = new;
}

void	checker_herdoc(t_parse *data)
{
	t_cmd_info	*cmd;
	t_tokens	*tok;
	int			s;

	cmd = data->cmd_info;
	while (cmd)
	{
		tok = cmd->token;
		s = -1;
		while (++s < cmd->nbr_token)
		{
			if (!ft_strcmp(tok->type, "in_file"))
				cmd->checker = -1;
			else if (!ft_strcmp(tok->type, "delim"))
				cmd->checker = s;
			tok = tok->next;
		}
		cmd = cmd->next;
	}
}

int	max_herdoc(t_parse *data)
{
	t_cmd_info	*cmd;
	t_tokens	*tok;
	int			l;
	int			i;
	int			s;

	i = -1;
	l = 0;
	cmd = data->cmd_info;
	while (++i < data->nbr_cmd)
	{
		s = -1;
		tok = cmd->token;
		while (++s < cmd->nbr_token)
		{
			if (!ft_strcmp(tok->type, "delim"))
				l++;
			tok = tok->next;
		}
		cmd = cmd->next;
	}
	if (l > 16)
		return (l);
	return (0);
}

void	expand_herdoc(t_parse *data)
{
	t_cmd_info	*cmd;
	t_tokens	*tok;
	int			i;
	int			s;

	i = -1;
	cmd = data->cmd_info;
	while (++i < data->nbr_cmd)
	{
		s = -1;
		tok = cmd->token;
		while (++s < cmd->nbr_token)
		{
			if (!g_int && !ft_strcmp(tok->type, "delim"))
				tok->str = read_herdoc(data, cmd, tok, s);
			if (g_int)
			{
				data->exit_status = 1;
				return ;
			}
			tok = tok->next;
		}
		cmd = cmd->next;
	}
}
