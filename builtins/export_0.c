/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 03:29:25 by mthamir           #+#    #+#             */
/*   Updated: 2024/09/18 02:49:16 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_index(t_parse **data)
{
	t_env	*env;

	env = (*data)->envir;
	while (env)
	{
		env->index = 0;
		env = env->next;
	}
}

void	init_first(char *var, char *egal, char *value, t_parse *data)
{
	t_env	*new;

	new = ft_env_malloc(sizeof(t_env), data);
	new->var = ft_strdup(var, data);
	new->egal = ft_strdup(egal, data);
	new->value = ft_strdup(value, data);
	new->next = NULL;
	data->envir = new;
}

void	add_to_env(char *var, char *egal, char *value, t_parse *data)
{
	t_env	*new;
	t_env	*node;

	node = data->envir;
	if (!data->envir)
		init_first(var, egal, value, data);
	else
	{
		new = ft_env_malloc(sizeof(t_env), data);
		while (node->next)
			node = node->next;
		new->var = ft_strdup(var, data);
		new->egal = ft_strdup(egal, data);
		new->value = ft_strdup(value, data);
		new->next = NULL;
		node->next = new;
	}
}

void	append_value(char *var, char *value, t_parse *data)
{
	t_env	*env;

	env = data->envir;
	while (env && ft_strcmp(env->var, var))
		env = env->next;
	env->egal = ft_strdup("=", data);
	env->value = ft_strjoin_env(env->value, value, data);
}

void	set_var_to_env(char *var, char *egal, char *value, t_parse *data)
{
	t_env	*env;

	env = data->envir;
	while (env)
	{
		if (!ft_strcmp(env->var, var))
			break ;
		env = env->next;
	}
	if (!env)
		return ;
	env->egal = ft_strdup(egal, data);
	env->value = ft_strdup(value, data);
}
