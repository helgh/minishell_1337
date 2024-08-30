/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:04:26 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/08/30 01:27:54 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*check_exit_status(char *str, char *itoa, int len, t_leaks **heap)
{
	int		i;
	int		n;
	char	*s;

	i = ft_strlen(itoa);
	n = ft_strlen(str);
	s = ft_malloc((i * len) + n + 1, heap);
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
	return (free(itoa), s);
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
	join = ft_malloc(len + 1, &data->heap);
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

	f = len;
	while (str[++f] && (ft_isalpha(str[f]) || str[f] == 95))
		;
	i = -1;
	while (data->envir[++i].var)
		if (ft_strncmp(&str[len + 1], data->envir[i].var, f - len - 1) == 0)
			break ;
	if (!data->envir[i].var)
		return (NULL);
	l = ft_strlen(data->envir[i].value);
	s = ft_malloc(l + 1, &data->heap);
	l = -1;
	while (data->envir[i].value[++l])
		s[l] = data->envir[i].value[l];
	s[l] = 0;
	data->flag = 1;
	return (s);
}

char	*set_value(t_parse *data, char *str, t_leaks **heap)
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
		s = check_exit_status(str, i_to_a(data->exit_status), len, heap);
	i = -1;
	while (s[++i])
	{
		if (s[i] == '$' && (ft_isalpha(s[i + 1]) || s[i + 1] == 95))
		{
			s = join_str(data, s, cmp_with_env(data, s, i), i);
			i = -1;
		}
		else if (s[i] == '$' && ft_isdigit(s[i + 1]))
			s = digit_with_dollar(data, s, i);
	}
	// printf("join = %s\n", s);
	return (s);
}
