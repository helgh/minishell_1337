/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_contu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:38:41 by mthamir           #+#    #+#             */
/*   Updated: 2024/09/10 17:17:37 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	same_dir(t_parse *data)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (perror("cd: "), 1);
	set_var_to_env("OLDPWD", "=", cwd, data);
	set_var_to_env("PWD", "=", cwd, data);
	return (free(cwd), 0);
}

int	to_the_root(t_parse *data)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (perror("cd: "), 1);
	if (chdir("/"))
		return (free(cwd), perror("cd"), 1);
	set_var_to_env("OLDPWD", "=", cwd, data);
	set_var_to_env("PWD", "=", "/", data);
	return (free(cwd), 0);
}

int	switch_the_old(t_parse *data)
{
	char	*old;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (perror("cd: "), 1);
	old = get_value("OLDPWD", data);
	if (!old)
		return (free(cwd), printf("M_H: cd: OLDPWD not set\n"), 1);
	if (old[0] == 0)
		return (free (cwd), printf("\n"));
	if (chdir(old))
		return (free(cwd), perror("cd: "), 1);
	set_var_to_env("OLDPWD", "=", cwd, data);
	set_var_to_env("PWD", "=", old, data);
	printf("%s\n", old);
	return (free(cwd), 0);
}

int	to_home(t_parse *data)
{
	char	*cwd;
	t_env	*head;
	char	*home;

	head = data->envir->next;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (perror("cd: "), 1);
	home = get_value("HOME", data);
	if (!home)
		return (free(cwd), printf("Error: cd: HOME not set\n"), 1);
	if (chdir(home))
		return (free(cwd), perror("cd: "), 1);
	set_var_to_env("OLDPWD", "=", cwd, data);
	set_var_to_env("PWD", "=", home, data);
	return (free(cwd), free(home), 0);
}
