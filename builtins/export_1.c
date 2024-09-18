/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 02:48:37 by mthamir           #+#    #+#             */
/*   Updated: 2024/09/18 03:01:11 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	already_exist(char *var, t_parse *data)
{
	t_env	*head;

	head = data->envir;
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
	int		i;
	char	*s;

	i = 0;
	s = str;
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
