/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 03:29:25 by mthamir           #+#    #+#             */
/*   Updated: 2024/08/30 04:12:45 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_to_env(char *var, char *egal,  char *value, t_parse *data)
{
	t_env *new;
	t_env *node;

	node = data->envir;
	new = ft_malloc(sizeof(t_env), &data->heap);
	if (!data->envir)
	{
		new->var = var;
		new->egal = egal;
		new->value = value;
		new->next = NULL;
		data->envir = new;
	}
	else
	{
		while (node->next)
			node = node->next;
		new->var = var;
		new->egal = egal;
		new->value = value;
		new->next = NULL;
		node->next = new;
	}
}

void print_export(int	fd, t_parse *data)
{
	t_env *env ;

	env = data->envir->next;
	while (env)
	{
		if (env->var)
		{
			putstr_fd("declare -x ", fd);
			putstr_fd(env->var, fd);
		}
		if (env->egal)
		{
			if (env->value)
			{
				putstr_fd(env->egal, fd);
				putstr_fd("\"", fd);
				putstr_fd(env->value, fd);
				putstr_fd("\"", fd);
			}
			else
			{
				putstr_fd(env->egal, fd);
				putstr_fd("\"", fd);
				putstr_fd("\"", fd);
			}
		}
		putstr_fd("\n", fd);
		env = env->next;
	}
}

void append_value(char *var,char *value, t_parse *data)
{
	t_env *env = data->envir;

	while (env->next && ft_strcmp(env->var, var))
		env = env->next;
	env->value = ft_strjoin(env->value, value, &data->heap);
}

void set_var_to_env(char *var, char *egal, char *value, t_parse *data)
{
	t_env *env = data->envir;

	while (env)
	{
		if (!ft_strcmp(env->var, var))
			break;
		env = env->next;
	}
	env->value = value;
	env->egal = egal;
}