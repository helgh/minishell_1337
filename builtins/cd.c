/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 02:10:54 by mthamir           #+#    #+#             */
/*   Updated: 2024/09/28 16:01:50 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_value(char *var, t_parse *data)
{
	t_env	*head;

	head = data->envir;
	while (head)
	{
		if (!ft_strcmp(head->var, var))
			return (ft_dup_str(head->value, data));
		head = head->next;
	}
	return (NULL);
}

void	print_cd_err(void)
{
	putstr_fd("cd: error retrieving current directory: ", 2);
	putstr_fd("getcwd: cannot access parent directories: ", 2);
	putstr_fd("No such file or directory\n", 2);
}

void	parent_removed(char *path, t_parse *data)
{
	char	*join1;
	char	*join2;

	join1 = ft_strjoin(get_value("PWD", data), "/", data);
	join2 = ft_strjoin(get_value("PWD", data), path, data);
	set_var_to_env("PWD", "=", join1, data);
	set_var_to_env("PWD", "=", join2, data);
}

int	go_to_path(char *path, t_parse *data)
{
	char	cwd[PATH_MAX];
	char	*pwd;

	if (!getcwd(cwd, sizeof(cwd)))
	{
		pwd = get_value("PWD", data);
		set_var_to_env("OLDPWD", "=", pwd, data);
		parent_removed(path, data);
		pwd = get_value("PWD", data);
		if (chdir(path))
			return (perror("cd :"), 1);
		set_var_to_env("PWD", "=", pwd, data);
		if (!getcwd(cwd, sizeof(cwd)))
			return (print_cd_err(), 1);
		else
			set_var_to_env("PWD", "=", cwd, data);
	}
	else
	{
		if (chdir(path) < 0)
			return (perror("cd"), 1);
		set_var_to_env("PWD", "=", getcwd(NULL, 0), data);
		set_var_to_env("OLDPWD", "=", cwd, data);
	}
	return (0);
}

int	cd(char **str, t_parse *data)
{
	char	*path;

	path = NULL;
	if (!str[1] || !ft_strcmp(str[1], "~"))
		return (to_home(data));
	else if (!ft_strcmp(str[1], "."))
		return (same_dir(data));
	else if (!ft_strcmp(str[1], "/.")
		|| !strcmp(str[1], "/..") || !ft_strcmp(str[1], "/"))
		return (to_the_root(data));
	else if (!ft_strcmp(str[1], "-"))
		return (switch_the_old(data), 0);
	if (go_to_path(str[1], data))
		return (1);
	return (0);
}
