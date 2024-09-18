/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 03:29:09 by mthamir           #+#    #+#             */
/*   Updated: 2024/09/18 03:45:17 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	s_d_end(char c)
{
	if (c == 34 || c == 39 || c == 0)
		return (1);
	return (0);
}

char	*exp_s_quotes(t_parse *data, t_tokens *tok, int *ind)
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

char	*count_cash_(char *str, int *ind, t_parse *data)
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
