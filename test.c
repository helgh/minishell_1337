/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:16:37 by mthamir           #+#    #+#             */
/*   Updated: 2024/08/06 17:42:44 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


 /* """""""hadi ra ri kantester biha hat tregel mzyan 3ad ndirha hta hya fl file */


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <string.h>


#define GET			1
#define SET			2
#define ADD			3
#define INIT		4
#define FREE_ALL	5

typedef struct s_leaks t_leaks;
typedef struct s_leaks
{
	void *adress;
	t_leaks *next;
}	t_leaks;

t_leaks *add_node(void *for_leaks, int operation)
{
	static t_leaks	*catch_leaks;
	static t_leaks	*head_leaks;
	static int		i;

	if (operation == ADD)
	{
		catch_leaks[i].adress = for_leaks;
		i++;
	}
	if (operation == FREE_ALL)
	{
		while (t < i)
		{
			free(catch_leaks[t].adress);
			t++;
		}
	}
	if (operation == 10)
		printf("printf ==== %s\n", (char *)catch_leaks->adress);

	if (operation == 66)
		return (catch_leaks);
	// printf("leaks ==== 0x%lx\n", (long)catch_leaks->adress);
	return (NULL);
}

void *ft_malloc(size_t size)
{
	char	*new;
	new = malloc (size);
	if (!new)
		return (NULL);	
	new[0] = 's';
	add_node(new, ADD);
	return (new);	
}

void f(void )
{
	system("leaks a.out");
}

int main()
{
	char *s = ft_malloc(100);
	// printf("s adress === %p\n", s);
	int i = -1;

	atexit(f);
	while (++i < 10)
		s[i] =  's';
	// s = NULL;
	// add_node(NULL, 10);
	t_leaks *ss = add_node(NULL, 66);
	// printf("%s\n", ss->adress);
}