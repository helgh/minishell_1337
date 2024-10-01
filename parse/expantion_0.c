/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 02:31:17 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/10/01 21:04:52 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count(t_parse *data, t_cmd_info *cmd, int flag)
{
	char		*type;
	int			i;
	int			nb;
	int			nb_files;
	t_tokens	*tok;

	i = -1;
	nb = 0;
	nb_files = 0;
	(void) data;
	tok = cmd->token;
	while (++i < cmd->nbr_token)
	{
		type = tok->type;
		if (!ft_strcmp(type, "cmd") || !ft_strcmp(type, "option")
			|| !ft_strcmp(type, "arg") || !ft_strcmp(type, "delim"))
			nb++;
		else if (ft_strcmp(type, "herdoc"))
			nb_files++;
		tok = tok->next;
	}
	if (flag == 0)
		return (nb);
	return (nb_files);
}

char	**div_arg(t_cmd_info *cmd, char **spl, int flag, t_exec *exec)
{
	int			i;
	int			s;
	t_tokens	*tok;

	tok = NULL;
	i = 0;
	s = 0;
	tok = cmd->token;
	while (tok)
	{
		if (!ft_strcmp(tok->type, "cmd") && tok->str && tok->str[0]
			&& i == 0)
			i = 1;
		else if ((!ft_strcmp(tok->type, "cmd")
				|| !ft_strcmp(tok->type, "option")
				|| !ft_strcmp(tok->type, "arg")) && tok->str && tok->str[0])
			spl[flag++] = tok->str;
		else if (!ft_strcmp(tok->type, "delim"))
			exec->herdoc = tok->str;
		else if (!ft_strcmp(tok->type, "in_file") && tok->str && tok->str[0])
			exec->herdoc = NULL;
		tok = tok->next;
	}
	spl[flag] = NULL;
	return (spl);
}

char	**cmd_opt_arg(t_parse *data, t_cmd_info *cmd, int len, t_exec *exec)
{
	t_tokens	*tok;
	char		**spl;
	int			flag;

	exec->flag_ambiguous = cmd->flag_ambiguous;
	spl = ft_malloc(sizeof(char *) * (len + 1), data);
	if (len == 0)
		return (spl[0] = NULL, spl);
	tok = cmd->token;
	flag = 0;
	while (tok)
	{
		if (!ft_strcmp(tok->type, "cmd") && tok->str && tok->str[0])
		{
			spl[0] = tok->str;
			flag = 1;
			exec->flag_ex = tok->flag_ex;
			break ;
		}
		tok = tok->next;
	}
	spl = div_arg(cmd, spl, flag, exec);
	return (spl);
}

char	**files(t_parse *data, t_cmd_info *cmd, int len)
{
	t_tokens	*tok;
	char		**spl;
	int			i;

	i = -1;
	if (len == 0)
		return (NULL);
	spl = ft_malloc(sizeof(char *) * (len + 1), data);
	tok = cmd->token;
	while (tok)
	{
		if (!ft_strcmp(tok->type, "red_in") || !ft_strcmp(tok->type, "red_out")
			|| !ft_strcmp(tok->type, "append"))
			spl[++i] = tok->str;
		else if (!ft_strcmp(tok->type, "in_file")
			|| !ft_strcmp(tok->type, "out_file")
			|| !ft_strcmp(tok->type, "app_file"))
			spl[++i] = tok->str;
		tok = tok->next;
	}
	spl[++i] = NULL;
	return (spl);
}

t_exec	*ready_for_exec(t_parse *data)
{
	t_cmd_info	*cmd;
	t_exec		*exec;
	t_exec		*tmp;
	int			i;

	cmd = data->cmd_info;
	i = -1;
	exec = NULL;
	while (++i < data->nbr_cmd)
	{
		tmp = ft_malloc(sizeof(t_exec), data);
		tmp->herdoc = NULL;
		tmp->cmd = cmd_opt_arg(data, cmd, count(data, cmd, 0), tmp);
		tmp->files = files(data, cmd, count(data, cmd, 1));
		tmp->red_in = 0;
		tmp->red_out = 1;
		tmp->red_herdoc = 0;
		tmp->check_flag = 0;
		tmp->pos = i;
		tmp->pid = 0;
		tmp->next = NULL;
		add_to_next(&exec, tmp);
		cmd = cmd->next;
	}
	return (exec);
}
