/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:48:07 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/08/18 18:19:37 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	add_node_to_struct(t_tokens **lst, t_tokens *new)
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

static void	add_to_struct(t_cmd_info **lst, t_cmd_info *new)
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

t_tokens	*tokens_struct(t_parse *info, t_cmd_info *cmd, t_leaks **heap)
{
	t_tokens	*tokens;
	int			i;
	int			s;
	char		*type;

	i = -1;
	while (++i < cmd->nbr_token)
	{
		s = -1;
		tokens = ft_malloc(sizeof(t_tokens), heap);
		tokens->str = cmd->all_token[i];
		tokens->type_qoute = set_flag_qoutes(tokens->str);
		tokens->sign_dollar = set_flag_dollar(tokens);
		while (tokens->str[++s])
			if (tokens->str[s] == -1)
				tokens->str[s] = 32;
		tokens->type = get_type_token(cmd->all_token, type, i, heap);
		type = tokens->type;
		tokens->next = NULL;
		add_node_to_struct(&info->token, tokens);
	}
	return (info->token);
}

t_cmd_info	*cmd_info_struct(t_parse *data_info)
{
	t_cmd_info	*cmd;
	int			i;
	int			s;

	i = -1;
	cmd = NULL;
	while (++i < data_info->nbr_cmd)
	{
		cmd = ft_malloc(sizeof(t_cmd_info), &data_info->heap);
		s = -1;
		cmd->cmd_line = data_info->all_cmd[i];
		cmd->all_token = ft_split(data_info->all_cmd[i], 32, &data_info->heap);
		cmd->nbr_token = 0;
		cmd->next = NULL;
		while (cmd->all_token[++s])
			cmd->nbr_token++;
		tokens_struct(data_info, cmd, &data_info->heap);
		add_to_struct(&data_info->cmd_info, cmd);
	}
	return (data_info->cmd_info);
}
