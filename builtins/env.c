/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 02:12:22 by mthamir           #+#    #+#             */
/*   Updated: 2024/09/12 22:45:12 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(char *s1, t_parse *data)
{
	int		i;
	char	*str;

	if (!s1)
		return (NULL);
	i = ft_strlen(s1);
	str = ft_env_malloc((i + 1) * sizeof(char), data);
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	ft_putstr(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(1, &str[i], 1);
}

void	init_env(char **env, t_parse *data)
{
	char	*pwd;
	char	*path;

	path = "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.";
	if (*env)
		global_env(env, data);
	else
	{
		pwd = getcwd(NULL, 0);
		add_to_env("OLDPWD", NULL, NULL, data);
		add_to_env("PWD", "=", pwd, data);
		add_to_env("SHLVL", "=", "1", data);
		add_to_env("_", "=", "/usr/bin/env", data);
		add_to_env("PATH", "=", path, data);
		free(pwd);
	}
}

int	print_env(t_parse *data)
{
	t_env	*env;

	env = data->envir;
	if (!env)
		return (putstr_fd("envirement id empty", 2), 1);
	while (env)
	{
		if (env->egal)
		{
			if (env->value)
			{
				ft_putstr(env->var);
				ft_putstr(env->egal);
				ft_putstr(env->value);
			}
			else
			{
				ft_putstr(env->var);
				ft_putstr(env->egal);
			}
			ft_putstr("\n");
		}
		env = env->next;
	}
	return (0);
}

void	global_env(char **env, t_parse *data)
{
	int		i;
	char	**spl;

	i = -1;
	spl = NULL;
	while (env[++i])
	{
		spl = spl_msh(env[i], '=', data);
		if (ft_strcmp(spl[0], "OLDPWD"))
			add_to_env(spl[0], "=", spl[1], data);
	}
	add_to_env("OLDPWD", NULL, NULL, data);
}
