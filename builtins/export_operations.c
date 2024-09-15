/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 03:29:25 by mthamir           #+#    #+#             */
/*   Updated: 2024/09/13 23:42:37 by hael-ghd         ###   ########.fr       */
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

int	sort_list(t_parse **data)
{
	t_env	*slow;
	t_env	*fast;
	int		max;

	init_index(data);
	slow = (*data)->envir;
	fast = (*data)->envir;
	while (slow)
	{
		fast = (*data)->envir;
		while (fast)
		{
			if (ft_strcmp(slow->var, fast->var) < 0)
			{
				fast->index++;
				max = fast->index;
			}
			fast = fast->next;
		}
		slow = slow->next;
	}
	return (max);
}

void init_first(char *var, char *egal, char *value, t_parse *data)
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

void	print_var(t_env env)
{
	if (env.var)
	{
		ft_putstr("declare -x ");
		ft_putstr(env.var);
	}
	if (env.egal)
	{
		if (env.value)
		{
			ft_putstr(env.egal);
			ft_putstr("\"");
			ft_putstr(env.value);
			ft_putstr("\"");
		}
		else
		{
			ft_putstr(env.egal);
			ft_putstr("\"");
			ft_putstr("\"");
		}
	}
	if (env.var)
		ft_putstr("\n");
}

int	print_export(t_parse *data)
{
	t_env	*env;
	int		index;
	int		max;

	init_index(&data);
	env = data->envir;
	if (!env)
		return (putstr_fd("envriment is empty\n", 2), 1);
	index = 0;
	max = sort_list(&data);
	while (1)
	{
		env = data->envir;
		while (env)
		{
			if (index > (max + 1))
				return (0);
			if (env->index == index)
				print_var(*env);
			env = env->next;
		}
		index++;
	}
	return (0);
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
