/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_qoutes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:41:22 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/08/19 21:26:03 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	length_line(char *str)
{
	int	i;
	int	n;

	i = -1;
	n = 0;
	while (str[++i])
	{
		if (str[i] == 124)
			n++;
		else if (str[i] == 60)
		{
			if (str[i + 1] == 60)
				i++;
			n++;
		}
		else if (str[i] == 62)
		{
			if (str[i + 1] == 62)
				i++;
			n++;
		}
	}
	n = ft_strlen(str) + (n * 2);
	return (n);
}

static int	s_d_qoutes(char *str, char *s, int *l)
{
	int		i;
	char	c;

	i = 0;
	c = *str;
	s[(*l)++] = c;
	str++;
	while (*str)
	{
		if (*str == 124)
			s[(*l)++] = -1;
		if (*str == c)
		{
			s[(*l)++] = c;
			return (++i);
		}
		if (*str != 124)
			s[(*l)++] = *str;
		i++;
		str++;
	}
	return (-1);
}

static void	space_between_oper(char *str, char *s, int *i, int *l)
{
	while (str[*i] && str[*i] != 34 && str[*i] != 39)
	{
		if (str[*i] == 124 || str[*i] == 60 || str[*i] == 62)
		{
			s[(*l)++] = 32;
			s[(*l)++] = str[*i];
			if (str[*i] != str[*i + 1])
				s[(*l)++] = 32;
			else
			{
				s[(*l)++] = str[*i];
				(*i)++;
				s[(*l)++] = 32;
			}
		}
		else
			s[(*l)++] = str[*i];
		(*i)++;
	}
	*i -= 1;
}

char	*check_qoutes(char *str, int len, t_parse *data_info)
{
	int	n;
	int	i;
	int	l;

	i = -1;
	n = 0;
	l = 0;
	data_info->line = ft_malloc(sizeof(char) * (len + 1), &data_info->heap);
	if (!data_info->line)
		return (printf("Failed allocation!\n"), NULL);
	while (str[++i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			n = s_d_qoutes(&str[i], data_info->line, &l);
			if (n == -1)
				return (printf("Unclosed qoutes!\n"), NULL);
			else
				i += n;
		}
		else
			space_between_oper(str, data_info->line, &i, &l);
	}
	data_info->line[l] = 0;
	return (data_info->line);
}
