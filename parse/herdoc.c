/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:44:54 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/09/16 03:12:07 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	glob_int;

static void	get_new_ind(char *str, int *ind)
{
	int	i;

	i = -1;
	while (str[++i] && str[i] == '$')
		;
	if (i % 2 != 0)
		*ind += (i - 1);
	else
		*ind += i;
}

static char	*remov_sign(char *str, t_parse *data)
{
	char	*s;
	int		i;
	int		l;

	i = -1;
	s = ft_malloc(ft_strlen(str) + 1, data);
	l = 0;
	while (str[++i])
	{
		if (str[i] == '$')
			get_new_ind(&str[i], &i);
		s[l++] = str[i];
	}
	s[l] = 0;
	return (s);
}

static char	*join_expand(t_parse *data, char *herdoc, char *new_line, int flag)
{
	char	*str;

	str = NULL;
	if (flag != 0)
	{
		new_line = remov_sign(new_line, data);
		herdoc = ft_strjoin(herdoc, new_line, data);
	}
	else
	{
		new_line = remov_sign(new_line, data);
		str = set_value_2(data, new_line);
		herdoc = ft_strjoin(herdoc, str, data);
	}
	return (herdoc);
}

static char	*read_herdoc(t_parse *data, char *str, int flag, int s)
{
	char	*line;
	char	*new_line;
	char	*herdoc;
	int		i;

	i = -1;
	herdoc = NULL;
	while (1)
	{
		signal_herdoc();
		line = readline("> ");
		if (!line)
			return (ft_restore_input(), ft_dup_str("\3", data));
		if (!ft_strcmp(str, line))
		{
			if (!herdoc)
				return (ft_dup_str("\3", data));
			return (free(line), herdoc);
		}
		if (*data->r_line)
			add_history(data->r_line);
		if (data->cmd_info->checker == -1 || data->cmd_info->checker != s)
			free(line);
		else
		{
			new_line = ft_strjoin(line, "\n", data);
			free (line);
			herdoc = join_expand(data, herdoc, new_line, flag);
		}
	}
	return (herdoc);
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
			if (!glob_int && !ft_strcmp(tok->type, "delim"))
				tok->str = read_herdoc(data, tok->str, tok->type_qoute, s);
			tok = tok->next;
		}
		cmd = cmd->next;
	}
}
