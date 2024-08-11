/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:31:12 by mthamir           #+#    #+#             */
/*   Updated: 2024/08/07 22:59:50 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

#include "libft_mini_shell/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#define GET		1
#define SET		2
#define ADD		3
#define INIT	4

typedef struct s_leaks
{
	char *adress;
	struct s_leaks *next;
}	t_leaks;


typedef struct s_env
{
	char *var;
	char *value;
}	t_env;

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*d1;
	unsigned char	*d2;

	d1 = (unsigned char *)s1;
	d2 = (unsigned char *)s2;
	i = 0;
	while (d1[i])
	{
		if (d1[i] != d2[i])
			return (d1[i] - d2[i]);
		i++;
	}
	return (0);
}

void add_node(void *for_leaks)
{
	static t_leaks	*catch_leaks;
	t_leaks *iterat;
	t_leaks	*new;

	new = malloc(sizeof(t_leaks));
	catch_leaks = new;
	iterat = catch_leaks;
	while (iterat->next)
		iterat = iterat->next;
	iterat->adress = for_leaks;
	iterat->next = NULL;
}

void *ft_malloc(size_t size)
{
	static void *for_leaks;

	for_leaks = malloc (size);
	if (!for_leaks)
		return (NULL);	
	add_node(for_leaks);
	return (for_leaks);	
}

t_env	*global_env(void *var, void *value, int operation)
{
	static t_env	env[ARG_MAX];
	void			*ret;
	static int		i;
	int				t;

	t = 0;
	if (operation == INIT)
	{
		env[i].var = var;
		env[i].value = value;
		i++;
	}
	else if (operation == GET)
		return (ret = env, ret);
	else if (operation == ADD)
	{
		env[i].var = var;
		env[i].value = value;
		env[i + 1].var = NULL;
		i++;
	}
	else if (operation == SET)
	{
		while (t < i && ft_strcmp(env[t].var, var) != 0)
			t++;
		env[t].value = value;
	}
	return (NULL);
}


void init_env(char **env)
{
	int i = 0;
	char **spl;

	spl = ft_split(env[i], '=');
	global_env(spl[0], spl[1], INIT);
	i++;
	while (env[i])
	{
		spl = ft_split(env[i], '=');
		global_env(spl[0], spl[1], ADD);
		i++;
	}
}

int main(int ac, char **av, char **env)
{
	int i = 0;
	char *str ;
	t_env *envr;

	
	init_env(env);
	// while (1)
	// {
	// 	str = readline("prompt: >");
	// 		add_history(str);
	// }
	global_env("SHLVL", "1", SET);
	envr = global_env("", "", GET);
	while (envr[i].var)
	{
		printf("%s=%s\n", envr[i].var, envr[i].value);
		i++;
	}
}
