/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 02:10:41 by mthamir           #+#    #+#             */
/*   Updated: 2024/09/12 01:00:16 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	check_export_parse(char *str, t_parse *data)
// {
// 	int		i;
// 	char	**spl;

// 	i = -1;
// 	spl = spl_msh(str, '=', data);
// 	if (!spl)
// 		return (1);
// 	if (!ft_isalpha(spl[0][0]) && spl[0][0] != '_')
// 		return (1);
// 	while (spl[0][++i + 1])
// 	{
// 		if (!ft_isalnum (spl[0][i]) && (spl[0][i] != '_'))
// 			return (1);
// 	}
// 	if (spl[0][i] != '+')
// 		if (!ft_isalnum(spl[0][i]) && spl[0][i] != '_')
// 			return (1);
// 	return (0);
// }

// void	export_with_value(char *str, t_parse *data)
// {
// 	char	**spl;

// 	spl = spl_msh(str, '=', data);
// 	if (spl && check_append (&spl[0]))
// 	{
// 		if (!already_exist (spl[0], data))
// 			append_value(spl[0], spl[1], data);
// 		else
// 			add_to_env(spl[0], "=", spl[1], data);
// 	}
// 	else if (spl && !already_exist(spl[0], data))
// 	{
// 		if (!spl[1])
// 			return ;
// 		else
// 			set_var_to_env(spl[0], "=", spl[1], data);
// 	}
// 	else if (spl)
// 	{
// 		if (!spl[1])
// 			add_to_env(spl[0], "=", NULL, data);
// 		else
// 			add_to_env(spl[0], "=", spl[1], data);
// 	}
// }

// void	_export_vars(char **str, t_parse *data)
// {
// 	int	i;
// 	int ret;

// 	i = 0;
// 	ret = 0;
// 	while (str[++i])
// 	{
// 		if (check_export_parse(str[i], data))
// 		{
// 			printf("M_H: export: %s : not a valid identifier\n", str[i]);
// 			ret = 1;
// 		}
// 		else
// 		{
// 			if (with_egal(str[i]))
// 				export_with_value(str[i], data);
// 			else
// 			{
// 				if (!already_exist(str[i], data))
// 					continue ;
// 				else
// 					add_to_env(str[i], NULL, NULL, data);
// 			}
// 		}
// 	}
// }

// void	_export(char **str, t_parse *data)
// {
// 	if (!str[1])
// 		return (print_export(data));
// 	else
// 		return (_export_vars(str, data));
// }

// void	init_index(t_parse **data)
// {
// 	t_env	*env;

// 	env = (*data)->envir;
// 	while (env)
// 	{
// 		env->index = 0;
// 		env = env->next;
// 	}
// }
