/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:53:52 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/09/11 21:08:18 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_flag_qoutes(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == 39)
			return (1);
		else if (str[i] == 34)
			return (2);
	}
	return (0);
}

int	set_flag_dollar(t_tokens *token)
{
	int	i;

	i = -1;
	while (token->str[++i])
	{
		if (token->str[i] == -1)
			token->str[i] = 32;
		else if (token->str[i] == -2)
			token->str[i] = '\t';
	}
	i = -1;
	while (token->str[++i])
	{
		if (token->type_qoute == 2 || token->type_qoute == 0)
			if (token->str[i] == '$')
				return (1);
	}
	return (0);
}

static int	check_option(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' && ft_isprint(str[i + 1]))
		return (0);
	if (str[i] == 34)
	{
		while (str[i] == 34)
			i++;
		if (str[i] != '-' || !str[i + 1])
			return (1);
	}
	else if (str[i] == 39)
	{
		while (str[i] == 39)
			i++;
		if (str[i] != '-' || !str[i + 1])
			return (1);
	}
	else
		return (1);
	return (0);
}

char	*get_type_token(char **spl, char *type, int s, t_parse *data)
{
	if (!ft_strcmp(spl[s], ">"))
		return (ft_dup_str("red_out", data));
	else if (!ft_strcmp(spl[s], "<"))
		return (ft_dup_str("red_in", data));
	else if (!ft_strcmp(spl[s], ">>"))
		return (ft_dup_str("append", data));
	else if (!ft_strcmp(spl[s], "<<"))
		return (ft_dup_str("herdoc", data));
	else if (s > 0 && !ft_strcmp(spl[s - 1], ">"))
		return (ft_dup_str("out_file", data));
	else if (s > 0 && !ft_strcmp(spl[s - 1], "<"))
		return (ft_dup_str("in_file", data));
	else if (s > 0 && !ft_strcmp(spl[s - 1], "<<"))
		return (ft_dup_str("delim", data));
	else if (s > 0 && !ft_strcmp(spl[s - 1], ">>"))
		return (ft_dup_str("app_file", data));
	else if (s > 0 && ft_strcmp(spl[0], "<<") && !ft_strcmp(type, "delim"))
		return (ft_dup_str("arg", data));
	else if (s == 0 || !ft_strcmp(type, "delim") || !ft_strcmp(type, "in_file")
			|| !ft_strcmp(type, "out_file"))
		return (ft_dup_str("cmd", data));
	else if (!check_option(spl[s]))
		if (!ft_strcmp(type, "cmd") || !ft_strcmp(type, "option"))
			return (ft_dup_str("option", data));
	return (ft_dup_str("arg", data));
}
