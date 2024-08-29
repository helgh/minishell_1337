/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:59:51 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/08/29 02:21:58 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*exp_without_quotes(t_parse *data, t_tokens *tok, int *ind, t_leaks **heap)
{
	char	*s;
	char	*str;
	char	**spl;
	int		i;

	i = -1;
	str = tok->str;
	while (str[++i + (*ind)] && str[i + (*ind)] != 34 && str[i + (*ind)] != 39)
		;
	s = sub_str(str, (*ind), i, heap);
	if (ft_strcmp(tok->type, "delim"))
		s = set_value(data, s, heap);
	spl = ft_split(s, 32, '\t', heap);
	if (*(spl + 1))
		s = NULL;
	while (data->flag == 1 && *spl)
	{
		s = ft_strjoin(s, *spl, heap);
		s = ft_strjoin(s, " ", heap);
		spl++;
	}
	data->flag = 0;
	*ind += i - 1;
	return (s);
}

static char	*exp_s_quotes(t_parse *data, t_tokens *tok, int *ind, t_leaks **heap)
{
	char	*s;
	char	*str;
	int		i;
	int		start;

	i = -1;
	(void) data;
	start = (*ind);
	str = tok->str;
	while (str[++i + (*ind) + 1] != 39)
		;
	s = sub_str(str, start + 1, i, heap);
	*ind += i + 1;
	return (s);
}

static char	*exp_d_quotes(t_parse *data, t_tokens *tok, int *ind, t_leaks **heap)
{
	char	*s;
	char	*str;
	char	*type;
	int		i;
	int		start;

	i = -1;
	start = (*ind);
	str = tok->str;
	type = tok->type;
	while (str[++i + (*ind) + 1] != 34)
		;
	s = sub_str(str, start + 1, i, heap);
	if (ft_strcmp(type, "delim"))
		s = set_value(data, s, heap);
	*ind += i + 1;
	return (s);
}

char	*exp_in_quotes(t_parse *data, t_tokens *tok, t_leaks **heap)
{
	char	*tmp;
	char	*s;
	int		i;
	int		ind;

	i = -1;
	s = NULL;
	ind = 0;
	while (tok->str[++i])
	{
		if (tok->str[i] == 34)
			tmp = exp_d_quotes(data, tok, &i, heap);
		else if (tok->str[i] == 39)
			tmp = exp_s_quotes(data, tok, &i, heap);
		else
			tmp = exp_without_quotes(data, tok, &i, heap);
		s = ft_strjoin(s, tmp, heap);
	}
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
			tok->str = exp_in_quotes(data, tok, &data->heap);
			prev = tok;
			tok = tok->next;
		}
		tmp = tmp->next;
	}
}
