/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:59:51 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/08/18 18:17:09 by hael-ghd         ###   ########.fr       */
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

void	expantion(t_parse *data, t_tokens *token)
{
	t_tokens	*tok;
	t_tokens	*prev;

	tok = token;
	prev = NULL;
	while (tok)
	{
		if (tok->type_qoute == 1)
			tok->str = remove_qoutes(tok->str, 39, &data->heap);
		else if (tok->type_qoute != 1)
		{
			if (tok->sign_dollar == 1)
				tok->str = set_value(data, tok->str, &data->heap);
			if (tok->type_qoute == 2)
				tok->str = remove_qoutes(tok->str, 34, &data->heap);
		}
		prev = tok;
		tok = tok->next;
	}
}
