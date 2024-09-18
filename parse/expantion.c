/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:59:51 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/09/18 03:37:21 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*exp_loop(t_parse *data, t_tokens *tok)
{
	char	*tmp;
	char	*s;
	char	*str;
	int		i;
	int		ind;

	i = -1;
	tmp = NULL;
	s = NULL;
	ind = 0;
	str = tok->str;
	while (str[++i])
	{
		if (str[i] == 39)
			tmp = exp_s_quotes(data, tok, &i);
		else if (str[i] == 34)
			tmp = exp_d_quotes(data, tok, &i, s);
		else
		{
			tmp = exp_without_quotes(data, tok, &i);
			tmp = handle_exp(data, tok, tmp);
		}
		s = ft_strjoin(s, tmp, data);
	}
	return (s);
}

char	*update(t_parse *data, char *str)
{
	char	*s;
	int		len;

	s = str;
	len = ft_strlen(s);
	while (--len >= 0)
	{
		if (s[len] == '\1' && s[len + 1] != 0)
			return (ft_dup_str(&s[len + 1], data));
	}
	return (str);
}

void	copy_until_quote(char *str, char *s, int *i, int *j)
{
	char	stop;

	stop = str[(*i)++];
	while (str[*i] && str[*i] != stop)
		s[(*j)++] = str[(*i)++];
	if (str[*i] == stop)
		(*i)++;
}

char	*exp_delimiter(t_parse *data, char *str)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	j = 0;
	s = ft_malloc(ft_strlen(str) + 1, data);
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			copy_until_quote(str, s, &i, &j);
		else if (str[i] == '$' && str[i + 1] == '$')
		{
			s[j++] = str[i++];
			s[j++] = str[i++];
		}
		else if (str[i] == '$' && (str[i + 1] == 34 || str[i + 1] == 39))
			i++;
		else
			s[j++] = str[i++];
	}
	s[j] = 0;
	return (s);
}

void	expantion(t_parse *data)
{
	t_tokens	*tok;
	t_tokens	*prev;
	t_cmd_info	*tmp;

	prev = NULL;
	tmp = data->cmd_info;
	while (tmp)
	{
		tok = tmp->token;
		while (tok)
		{
			if (ft_strcmp(tok->type, "delim"))
			{
				tok->str = exp_loop(data, tok);
				tok->str = update(data, tok->str);
			}
			else
				tok->str = exp_delimiter(data, tok->str);
			prev = tok;
			tok = tok->next;
		}
		tmp = tmp->next;
	}
}
