/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:48:07 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/09/22 17:25:10 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	add_to_cmd_info(t_cmd_info **lst, t_cmd_info *new)
{
	t_cmd_info	*ptr;

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

static void	add_to_token(t_tokens **lst, t_tokens *new)
{
	t_tokens	*ptr;

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

t_tokens	*tokens_struct(t_cmd_info *cmd, t_parse *data)
{
	t_tokens	*tokens;
	int			i;
	int			s;
	char		*type;

	i = -1;
	while (++i < cmd->nbr_token)
	{
		s = -1;
		tokens = ft_malloc(sizeof(t_tokens), data);
		tokens->str = cmd->all_token[i];
		tokens->flag_ex = 0;
		tokens->type_qoute = set_flag_qoutes(tokens->str);
		tokens->sign_dollar = set_flag_dollar(tokens);
		tokens->type = get_type_token(cmd->all_token, type, i, data);
		tokens->flag_ambiguous = 0;
		type = tokens->type;
		tokens->next = NULL;
		add_to_token(&cmd->token, tokens);
	}
	return (cmd->token);
}

t_cmd_info	*cmd_info_struct(t_parse *data)
{
	t_cmd_info	*cmd;
	int			i;
	int			s;

	i = -1;
	cmd = NULL;
	while (++i < data->nbr_cmd)
	{
		cmd = ft_malloc(sizeof(t_cmd_info), data);
		s = -1;
		cmd->cmd_line = data->all_cmd[i];
		cmd->all_token = ft_split(data->all_cmd[i], 32, '\t', data);
		cmd->nbr_token = 0;
		cmd->flag_ambiguous = 0;
		cmd->checker = -1;
		cmd->next = NULL;
		cmd->token = NULL;
		while (cmd->all_token[++s])
			cmd->nbr_token++;
		add_to_cmd_info(&data->cmd_info, cmd);
		tokens_struct(cmd, data);
	}
	return (data->cmd_info);
}
