/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:37:44 by mthamir           #+#    #+#             */
/*   Updated: 2024/08/24 18:39:49 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(char **env, t_parse *data)
{
	char *pwd;


	if (env)
		global_env(env, data);
	else
	{
		pwd = getcwd(NULL, 0);
		add_to_env("OLDPWD", NULL, NULL, data);
		add_to_env("PWD", "=", pwd, data);
		add_to_env("SHLVL", "=", "1", data );
		add_to_env("_", "=", "/usr/bin/env", data );
	}
}
/*________________________________________________________________________________*/
/* function used to add a variable to the envirement "export var=value" */


void	add_to_env(char *var, char *egal,  char *value, t_parse *data)
{
	t_env *new;
	t_env *node;
	
	// if(!pars_variable(var))
	// 	printf("%s\n", var);
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

void print_env(char *file, t_parse *data)
{
	t_env *env = data->envir;
	int fd;

	fd = check_acsses_file(file);
	while (env)
	{
		if (env->egal)
		{
			if (env->value)
			{
				putstr_fd(env->var, fd);
				putstr_fd(env->egal, fd);
				putstr_fd(env->value, fd);
				putstr_fd("\n", fd);
			}
			else
			{
				putstr_fd(env->var, fd);
				putstr_fd(env->egal, fd);
			}
		}
		env = env->next;
	}
}


int with_egal(char *str)
{
	int i = 0;

	while (str[i])
		i++;
	i--;
	while (i > 0)
	{
		if (str[i] == 32 || str[i] == 9)
			i--;
		else if (str[i] == '=')
			return (1);
		else
			break;
	}
	return (0);
}

/*________________________________________________________________________________*/
/*function for the globale envirement to be used wherever i want*/

void	global_env(char **env, t_parse *data)
{
	int i = 0;
	char **spl;

	while (env[i])
	{
		spl = spl_msh(env[i], '=', &data->heap);
		if (!spl[1])
		{
			if (with_egal(env[i]))
				add_to_env(spl[0], "=", NULL, data);
			else
				add_to_env(spl[0], NULL, NULL, data);
		}
		else
			add_to_env(spl[0], "=", spl[1], data);
		i++;
	}
}

