/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:59:51 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/09/17 23:56:52 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	s_d_end(char c)
{
	if (c == 34 || c == 39 || c == 0)
		return (1);
	return (0);
}

static char	*exp_s_quotes(t_parse *data, t_tokens *tok, int *ind)
{
	char	*s;
	char	*str;
	int		i;
	int		start;

	i = -1;
	start = (*ind);
	str = tok->str;
	while (str[++i + (*ind) + 1] != 39)
		;
	s = sub_str(str, start + 1, i, data);
	*ind += i + 1;
	return (s);
}

char	*get_str(char *str, int *ind, t_parse *data)
{
	char	*s;
	int		i;

	i = -1;
	s = NULL;
	while (str[++i] && str[i] != 34 && str[i] != '$')
		;
	s = sub_str(str, 0, i, data);
	*ind += (i - 1);
	return (s);
}

char	*no_expand(t_parse *data, char *str, int *ind)
{
	char	*s;
	int		i;

	i = -1;
	s = NULL;
	(void) data;
	if (str[0] == '$' && !str[1])
		return (ft_dup_str("$", data));
	while (!s_d_end(str[++i]) && str[i] != '$')
		;
	if (i != 0)
	{
		s = sub_str(str, 0, i, data);
		*ind += (i - 1);
	}
	return (s);
}

char	*count_$_(char *str, int *ind, t_parse *data)
{
	char	*s;
	int		i;
	int		n;

	i = -1;
	s = NULL;
	while (str[++i] == '$')
		;
	if (i % 2 == 0)
		*ind += (i - 1);
	else if (str[i] == '?')
	{
		s = sub_str(str, i - 1, 2, data);
		*ind += i;
	}
	else
	{
		n = -1;
		while (str[++n + i] && (ft_isalnum(str[n + i]) || str[n + i] == 95))
			;
		s = sub_str(str, i - 1, n + 1, data);
		*ind += (i + n - 1);
	}
	return (s);
}

static char	*exp_d_quotes(t_parse *data, t_tokens *tok, int *ind, char *line)
{
	char	*s;
	char	*tmp;
	char	*str;
	int		i;

	i = -1;
	str = tok->str;
	s = NULL;
	tmp = NULL;
	while (str[++i + (*ind) + 1] != 34)
	{
		if (str[i + (*ind) + 1] == '$' && str[i + (*ind) + 2] == 34)
			tmp = count_$_(&str[i + (*ind) + 1], &i, data);
		else if (str[i + (*ind) + 1] == '$')
		{
			tmp = count_$_(&str[i + (*ind) + 1], &i, data);
			if (tmp)
				tmp = set_value(data, tmp);
		}
		else
			tmp = get_str(&str[i + (*ind) + 1], &i, data);
		s = ft_strjoin(s, tmp, data);
	}
	if ((!s || !s[0]) && !line)
		s = ft_dup_str("\1", data);
	*ind += (i + 1);
	return (s);
}

static int	sign_in_end(char *str, int *ind)
{
	int	i;

	i = -1;
	while (str[++i] == '$')
		;
	if (str[i] == 34 || str[i] == 39)
	{
		*ind += (i - 1);
		return (1);
	}
	return (0);
}

static char	*exp_without_quotes(t_parse *data, t_tokens *tok, int *ind)
{
	char	*s;
	char	*tmp;
	char	*str;
	int		i;

	i = -1;
	str = tok->str;
	tmp = NULL;
	s = NULL;
	while (!s_d_end(str[++i + (*ind)]))
	{
		if (sign_in_end(&str[i + (*ind)], &i))
			;
		else if (str[i + (*ind)] == '$' && !s_d_end(str[i + (*ind) + 1]))
		{
			tmp = count_$_(&str[i + (*ind)], &i, data);
			if (tmp)
				tmp = set_value(data, tmp);
		}
		else
			tmp = no_expand(data, &str[i + (*ind)], &i);
		s = ft_strjoin(s, tmp, data);
	}
	*ind += i - 1;
	return (s);
}

char	*handle_exp(t_parse *data, t_tokens *tok, char *s)
{
	char	**spl;

	spl = ft_split(s, 32, '\t', data);
	if (spl && *spl && *(spl + 1))
	{
		s = NULL;
		while (*(spl + 1))
		{
			s = ft_strjoin(s, *spl, data);
			s = ft_strjoin(s, " ", data);
			spl++;
			tok->flag_ex = 1;
		}
		s = ft_strjoin(s, *spl, data);
	}
	return (s);
}

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
