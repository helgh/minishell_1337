/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:59:51 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/08/28 03:05:17 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_new_str(char *str, char c)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		while (str[i] && str[i] != c)
			i++;
		if (str[i++] == c)
			count++;
		while (str[i] && str[i] != c)
			i++;
		if (str[i] == 0)
			return (count * 2);
	}
	return (count * 2);
}

char	*remove_qoutes(char *str, char c, t_leaks **heap)
{
	int		len;
	int		i;
	char	*s;

	len = count_new_str(str, c);
	i = -1;
	s = ft_malloc((ft_strlen(str) - len) + 1, heap);
	len = 0;
	while (str[++i])
		if (str[i] && str[i] != c)
			s[len++] = str[i];
	s[len] = 0;
	return (s);
}

static char	*exp_without_quotes(t_parse *data, char *str, int *ind, t_leaks **heap)
{
	char	*s;
	char	**spl;
	int		i;
	int		start;

	i = -1;
	start = (*ind);
	while (str[++i] && str[i] != 34 && str[i] != 39)
		;
	s = sub_str(str, 0, i, heap);
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

static char	*exp_s_quotes(t_parse *data, char *str, int *ind, t_leaks **heap)
{
	char	*s;
	int		i;
	int		start;

	i = -1;
	(void) data;
	start = (*ind);
	while (str[++i] != 39)
		;
	s = sub_str(str, 0, i, heap);
	*ind += i + 1;
	return (s);
}

static char	*exp_d_quotes(t_parse *data, char *str, int *ind, t_leaks **heap)
{
	char	*s;
	int		i;
	int		start;

	i = -1;
	start = (*ind);
	while (str[++i] != 34)
		;
	s = sub_str(str, 0, i, heap);
	s = set_value(data, s, heap);
	*ind += i + 1;
	return (s);
}

char	*exp_in_quotes(t_parse *data, char *str, t_leaks **heap)
{
	char	*tmp;
	char	*s;
	int		i;
	int		ind;

	i = -1;
	s = NULL;
	ind = 0;
	while (str[++i])
	{
		if (str[i] == 34)
			tmp = exp_d_quotes(data, &str[i + 1], &i, heap);
		else if (str[i] == 39)
			tmp = exp_s_quotes(data, &str[i + 1], &i, heap);
		else
			tmp = exp_without_quotes(data, &str[i], &i, heap);
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
			tok->str = exp_in_quotes(data, tok->str, &data->heap);
			prev = tok;
			tok = tok->next;
		}
		tmp = tmp->next;
	}
}
