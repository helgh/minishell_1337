/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 02:12:22 by mthamir           #+#    #+#             */
/*   Updated: 2024/08/30 04:12:27 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void	init_env(char **env, t_parse *data)
{
	char *pwd;

	if (*env)
		global_env(env, data);
	else
	{
		pwd = getcwd(NULL, 0);
		add_to_env("OLDPWD", NULL, NULL, data);
		add_to_env("PWD", "=", pwd, data);
		add_to_env("SHLVL", "=", "1", data );
		add_to_env("_", "=", "/usr/bin/env", data );
		add_to_env("PATH", "=", "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", data );
	}
}

void print_env(int	fd, t_parse *data)
{
	t_env *env = data->envir;

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
				add_to_env(spl[0], "=", "", data);
			else
				add_to_env(spl[0], "", "", data);
		}
		else
			add_to_env(spl[0], "=", spl[1], data);
		i++;
	}
}
