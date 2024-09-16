/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:04:26 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/09/16 03:04:07 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*check_exit_status(char *str, char *itoa, int len, t_parse *data)
{
	int		i;
	int		n;
	char	*s;

	i = ft_strlen(itoa);
	n = ft_strlen(str);
	s = ft_malloc((i * len) + n + 1, data);
	n = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			i++;
			len = -1;
			while (itoa[++len])
				s[n++] = itoa[len];
		}
		else
			s[n++] = str[i];
	}
	s[n] = 0;
	return (s);
}

static char	*digit_with_dollar(t_parse *data, char *str, int l)
{
	int		i;
	int		len;
	char	*join;
	int		n;

	i = l;
	i += 2;
	len = (ft_strlen(str) - (i - l));
	join = ft_malloc(len + 1, data);
	n = -1;
	while (++n < l)
		join[n] = str[n];
	while (i < ft_strlen(str))
		join[n++] = str[i++];
	join[n] = 0;
	return (join);
}

static char	*cmp_with_env(t_parse *data, char *str, int len)
{
	int		i;
	int		l;
	int		f;
	char	*s;
	t_env	*tmp;

	f = len;
	tmp = data->envir;
	while (str[++f] && (ft_isalnum(str[f]) || str[f] == 95))
		;
	i = -1;
	while (tmp)
	{
		if (ft_strncmp(&str[len + 1], tmp->var, f - len - 1) == 0)
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		return (ft_dup_str("", data));
	l = ft_strlen(tmp->value);
	s = ft_malloc(l + 1, data);
	l = -1;
	while (tmp->value && tmp->value[++l])
		s[l] = tmp->value[l];
	s[l] = 0;
	return (s);
}

char	*set_value_2(t_parse *data, char *str)
{
	int		i;
	int		len;
	char	*s;

	i = -1;
	len = 0;
	s = str;
	while (str[++i])
		if (str[i] == '$' && str[i + 1] == '?')
			len++;
	if (len != 0)
		s = check_exit_status(str, i_to_a(data->exit_status, data), len, data);
	i = -1;
	while (str[++i])
	{
		if (s[i] == '$' && (ft_isalpha(s[i + 1]) || s[i + 1] == 95))
		{
			s = join_str(data, s, cmp_with_env(data, s, i), i);
			i = -1;
		}
		else if (s[i] == '$' && ft_isdigit(s[i + 1]))
			s = digit_with_dollar(data, s, i);
	}
	return (s);
}

char	*set_value(t_parse *data, char *str)
{
	int		i;
	int		len;
	char	*s;

	i = -1;
	len = 0;
	s = str;
	while (str[++i])
		if (str[i] == '$' && str[i + 1] == '?')
			len++;
	if (len != 0)
		s = check_exit_status(str, i_to_a(data->exit_status, data), len, data);
	i = -1;
	if (s[++i] == '$' && (ft_isalpha(s[i + 1]) || s[i + 1] == 95))
		s = cmp_with_env(data, s, i);
	else if (s[i] == '$' && ft_isdigit(s[i + 1]))
		s = digit_with_dollar(data, s, i);
	return (s);
}
