/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:01:04 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/07/30 15:04:14 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*ft_strdup(const char *s1);
int	ft_strcmp(char *s1, char *s2);
size_t	ft_strlen(const char *s);

char	**sort_ascii(char **envir, int len)
{
	int		i;
	int		size;
	char	*env;

	i = 0;
	env = NULL;
	size = len - 1;
	while (size > 0)
	{
		i = 0;
		while (i < size)
		{
			if (ft_strcmp(envir[i], envir[i + 1]) == 2)
			{
				env = envir[i];
				envir[i] = envir[i + 1];
				envir[i + 1] = env;
			}
			i++;
		}
		size--;
	}
	return (envir);
}

void	ft_cd(char **env, char *str)
{
	int	i;

	i = 0;
	
}

char	**ft_export(char **env, char *str)
{
	int		i;
	char	**envir;
	char	**env_copy;

	env_copy = env;
	i = 0;
	while (*(env_copy++))
		i++;
	if (str)
		i++;
	envir = malloc (sizeof(char *) * (i + 1));
	if (!envir)
		return (NULL);
	i = -1;
	while (env[++i])
		envir[i] = ft_strdup(env[i]);
	if (str)
		envir[i++] = ft_strdup(str);
	envir[i] = NULL;
	env_copy = sort_ascii(envir, i);
	return (env_copy);
}

int main(int ac, char **av, char **envp)
{
	char	**export;
	int		i = -1;

	export = ft_export(envp, "Hello");
	while (export[++i])
	{
		// printf("envp = %s\n", envp[i]);
		printf("export = %s\n", export[i]);
	}
}