/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 02:11:28 by mthamir           #+#    #+#             */
/*   Updated: 2024/08/30 03:26:45 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_var_from_env(char	*var, t_parse *data)
{
	t_env *tmp;
	t_env *tmp1;
	t_env *env ;

	env = data->envir;
	if (!pars_variable(var))
		{
			printf("syntax error");
			exit(0);
		}
	while (env->next && ft_strcmp(env->next->var, var))
		env = env->next;
	if (!env->next)
		return ;
	if (!ft_strcmp(env->next->var, var))
	{
		tmp = env;
		tmp1 = tmp->next;
		tmp1->next = NULL;
		env = env->next->next;
		tmp->next = env;
		free(tmp1);
	}
}


void	_unset(t_parse *data)
{
	char **str ;
	int i = 1;
	str = ft_split(data->r_line, 32, 9, &data->heap);

	while (str[i])
	{
		unset_var_from_env(str[i], data);
		i++;
	}
}