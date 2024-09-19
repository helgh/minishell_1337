/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 03:29:27 by mthamir           #+#    #+#             */
/*   Updated: 2024/09/20 00:36:28 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_vars_x_d_q(int *i, char **s, char **tmp)
{
	*i = -1;
	*s = NULL;
	*tmp = NULL;
}

char	*exp_d_quotes(t_parse *data, t_tokens *tok, int *ind, char *line)
{
	char	*s;
	char	*tmp;
	char	*str;
	int		i;

	init_vars_x_d_q(&i, &s, &tmp);
	str = tok->str;
	while (str[++i + (*ind) + 1] != 34)
	{
		if (str[i + (*ind) + 1] == '$' && str[i + (*ind) + 2] == 34)
			tmp = count_cash_(&str[i + (*ind) + 1], &i, data);
		else if (str[i + (*ind) + 1] == '$')
		{
			tmp = count_cash_(&str[i + (*ind) + 1], &i, data);
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

int	sign_in_end(char *str, int *ind)
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

char	*exp_without_quotes(t_parse *data, t_tokens *tok, int *ind)
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
			tmp = count_cash_(&str[i + (*ind)], &i, data);
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
