/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:44:54 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/09/21 23:32:11 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_int;

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

static char	*herdoc_value(t_parse *data, char *line, char *str, char *herdoc)
{
	if (!line && g_int)
		return (ft_restore_input(data), NULL);
	if (!ft_strcmp(str, line))
	{
		if (!herdoc)
			return (free(line), ft_dup_str("\3", data));
		return (free(line), herdoc);
	}
	if (!herdoc)
		return (ft_dup_str("\033[F> ", data));
	return (ft_strjoin("\033[F> ", herdoc, data));
}

char	*read_herdoc(t_parse *data, t_cmd_info *cmd, t_tokens *tok, int s)
{
	char	*line;
	char	*new_line;
	char	*herdoc;

	herdoc = NULL;
	signal_herdoc();
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(tok->str, line))
			return (herdoc_value(data, line, tok->str, herdoc));
		if (cmd->checker == -1 || cmd->checker != s)
			free(line);
		else
		{
			new_line = ft_strjoin(line, "\n", data);
			free (line);
			herdoc = join_expand(data, herdoc, new_line, tok->type_qoute);
		}
	}
	return (herdoc);
}
