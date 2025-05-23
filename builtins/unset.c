/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 02:11:28 by mthamir           #+#    #+#             */
/*   Updated: 2024/09/27 18:18:15 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_unset_parse(char *var)
{
	int	i;

	i = -1;
	while (var[++i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (1);
		if (i == 0 && !ft_isalpha(var[i]) && var[i] != '_')
			return (1);
	}
	return (0);
}

static int	unset_var_from_env(char	*var, t_parse *data)
{
	t_env	*env;
	t_env	*tmp;

	env = data->envir;
	if (check_unset_parse(var))
	{
		putstr_fd("M_H: unset: `", 2);
		putstr_fd(var, 2);
		putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	if (env && !ft_strcmp(env->var, var))
		return (data->envir = env->next, 0);
	while (env)
	{
		if (!ft_strcmp(env->var, var))
			break ;
		tmp = env;
		env = env->next;
	}
	if (env)
		tmp->next = env->next;
	return (0);
}

int	_unset(char **str, t_parse *data)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (str[++i])
		if (unset_var_from_env(str[i], data))
			ret = 1;
	return (ret);
}
