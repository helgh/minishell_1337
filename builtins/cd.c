/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 02:10:54 by mthamir           #+#    #+#             */
/*   Updated: 2024/08/31 02:35:50 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*We convert the input path to lowercase to handle case-insensitive comparisons.
We split the path into components using '/' as a delimiter.
We remove empty components and redundant separators like "/./".
We handle "./" and "../" components appropriately.
We join the remaining components into a normalized path string.
We allocate and deallocate memory properly to avoid memory leaks.*/

void same_dir(t_parse *data)
{
	char *cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (perror("getcwd"), 1);
	set_var_to_env("OLDPWD", "=", cwd, data);	
	set_var_to_env("PWD", "=", cwd, data);
	return (free(cwd), 0);
}

int change_dir()
{
	if (chdir("/"))
		return (perror("cd"), 1);
	return (0);
}

int	to_the_root(t_parse *data)
{
	char *cwd;
	
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (perror("getcwd"), 1);
	if (change_dir())
		return ;
	set_var_to_env("OLDPWD", "=", cwd, data);
	set_var_to_env("PWD", "=", cwd, data);
	return (0);
}

int switch_the_old(t_parse *data)
{
	t_env *head;
	char *cwd;
	char *oldpwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (perror("getcwd"), 1);
	head = data->envir;
	while (head)
	{
		if (!strcmp(head->var ,"OLDPWD"))
		{
			if (!head->value)
				return(printf("M_H: cd: OLDPWD not set"), 1);
			printf("%s\n", head->value);
			oldpwd = ft_dup_str(head->value, &data->heap);
			set_var_to_env("OLDPWD", "=", oldpwd, data);
			set_var_to_env("PWD", "=", cwd, data);
			break;
		}
		head = head->next;
	}
	return (0);
}

int	to_home(t_parse *data)
{
	char *cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (perror("getcwd"), 1);
	if (chdir("/Users/mthamir"))
		return (perror("chdir"), 1);
	set_var_to_env("OLDPWD", "=", cwd, data);
	set_var_to_env("PWD", "=", "/Users/mthamir", data);
}

char	*get_real_path(char *str, t_parse *data)
{
	int i = 0;
	int j = 0;
	char path[1024];

	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '.')
			path[j] = '.';
		else if (str[i] == '/')
		{
			path[j] = '/';
			while(str[i++] == '/');
		}
		else
			path[j] = str[i];
		i++;
		j++;
	}
	path[j] = 0;
}

int cd(char **str, t_parse *data)
{
	char *path;

	path = get_real_path(str[1], data);
	if (!str[1] || !strcmp(str[1], "~"))
		return (to_home(data));	
	else if (!strcmp(str[1], "."))
		return (same_dir(data), 0);
	else if(!strcmp(str[1], "/.") || !strcmp(str[1], "/.."))
		return (to_the_root(data), 0);
	else if (!strcmp(str[1], "-"))
		return (switch_the_old(data), 0);
	else
		go_to_path(str[1] , data);
}