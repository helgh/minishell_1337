/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:53:52 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/08/18 18:20:25 by hael-ghd         ###   ########.fr       */
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
		if (token->type_qoute == 2 || token->type_qoute == 0)
			if (token->str[i] == '$')
				return(1);
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

char	*get_type_token(char **spl, char *type, int s, t_leaks **heap)
{
	if (!ft_strcmp(spl[s], ">"))
		return (ft_dup_str("red_out", heap));
	else if (!ft_strcmp(spl[s], "<"))
		return (ft_dup_str("red_in", heap));
	else if (!ft_strcmp(spl[s], ">>"))
		return (ft_dup_str("append", heap));
	else if (!ft_strcmp(spl[s], "<<"))
		return (ft_dup_str("herdoc", heap));
	else if (s > 0 && !ft_strcmp(spl[s - 1], ">"))
		return (ft_dup_str("out_file", heap));
	else if (s > 0 && !ft_strcmp(spl[s - 1], "<"))
		return (ft_dup_str("in_file", heap));
	else if (s > 0 && !ft_strcmp(spl[s - 1], "<<"))
		return (ft_dup_str("delim", heap));
	else if (s > 0 && !ft_strcmp(spl[s - 1], ">>"))
		return (ft_dup_str("app_file", heap));
	else if (s == 0 || !ft_strcmp(type, "delim") || !ft_strcmp(type, "in_file"))
		return (ft_dup_str("cmd", heap));
	else if (!check_option(spl[s]) && (!ft_strcmp(type, "cmd") || !ft_strcmp(type, "option")))
		return (ft_dup_str("option", heap));
	return (ft_dup_str("arg", heap));
}
