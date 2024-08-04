/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:31:12 by mthamir           #+#    #+#             */
/*   Updated: 2024/08/04 16:41:11 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*d1;
	unsigned char	*d2;

	d1 = (unsigned char *)s1;
	d2 = (unsigned char *)s2;
	i = 0;
	while (d1[i] != '=' || d2[i] != '\0')
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

t_env	*global_env(void	*var, void	*value, int operation)
{
	static t_env	env[ARG_MAX];
	void	*ret;
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

	{
		ret = env;
		return (ret);
	}
	else if (operation == ADD)
	{
		env[i].var = var;
		env[i].value = value;
		env[i + 1].var = NULL;
		// printf("%s=%s\n", env[i].var, env[i].value);
		i++;
	}
	else if (operation == SET)
	{
		while (t < i && ft_strcmp(env[i].var, var))
			t++;
		env->value = value;
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
	// envr = global_env("", "", GET);
	// while (envr[i].var)
	// {
	// 	printf("%s=%s\n", envr[i].var, envr[i].value);
	// 	i++;
	// }
} 