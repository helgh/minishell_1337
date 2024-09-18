/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 00:03:46 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/09/18 03:10:18 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*path_env(char **envp)
{
	char	*envir;

	while (ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	envir = ft_strnstr(*envp, "/", 6);
	return (envir);
}

static int	check_slash(char *str)
{
	int	i;

	i = -1;
	while (str && str[++i])
	{
		if (str[i] == '/')
			return (1);
	}
	return (0);
}

static char	**get_cmd(t_parse *data, t_exec *ex)
{
	int		i;
	char	*str;

	i = -1;
	str = NULL;
	if (ex->flag_ex)
	{
		i = -1;
		while (ex->cmd[++i])
		{
			str = ft_strjoin(str, ex->cmd[i], data);
			str = ft_strjoin(str, " ", data);
		}
		return (ft_split(str, 32, 32, data));
	}
	return (ex->cmd);
}

char	*check_access(t_parse *data, t_exec *ex)
{
	char	**spl_env;
	char	**s;
	char	*path;

	spl_env = ft_split(path_env(data->env), ':', ':', data);
	s = spl_env;
	ex->cmd = get_cmd(data, ex);
	if (!ex->cmd)
		return (NULL);
	path = ex->cmd[0];
	while (!check_slash(ex->cmd[0]) && *(spl_env++) != NULL)
	{
		*spl_env = ft_strjoin(*spl_env, "/", data);
		path = ft_strjoin(*spl_env, ex->cmd[0], data);
		if (access(path, F_OK | X_OK) == -1 && *(spl_env + 1) == NULL)
		{
			putstr_fd("M_H: ", 2);
			putstr_fd(ex->cmd[0], 2);
			putstr_fd(": command not found\n", 2);
			return (NULL);
		}
		else if (access(path, F_OK | X_OK) != -1)
			break ;
	}
	return (path);
}
