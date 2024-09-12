/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 02:57:28 by mthamir           #+#    #+#             */
/*   Updated: 2024/09/06 16:28:28 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void check_cmd(t_parse *data)
// {
// 	char **str;

// 	str = ft_split(data->r_line, 32, 9, &data->heap);
// 	if(!ft_strcmp(str[0], "export"))
// 		_export(1 , data);
// 	else if(!ft_strcmp(str[0], "env"))
// 		print_env(1,data);
// 	else if(!ft_strcmp(str[0], "pwd"))
// 		get_pwd(1);
// 	else if (!strcmp(str[0], "unset"))
// 		_unset(data);
// 	else if (!strcmp(str[0], "exit"))
// 		ft_exit(str, data);
// }

// // int is_special_char(char c)
// // {
// // 	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
// // 		return (1);
// // 	if (c >= '0' && c <= '9')
// // 		return (1);
// // 	return (0);
// // }

int already_exist(char *var, t_parse *data)
{
	t_env *head = data->envir;

	while (head)
	{
		if (!ft_strcmp(var, head->var))
			return (0);
		head = head->next;
	}
	return (1);
}

int	check_append(char **str)
{
	int i = 0;
	char *s = *str;

	while (s[i])
		i++;
	if (i > 0)
		i--;
	if (s[i] == '+')
	{
		s[i] = 0;
		return (1);
	}
	return (0);
}
