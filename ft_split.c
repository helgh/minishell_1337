/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:42:08 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/08/15 06:21:02 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft_mini_shell/libft.h"
#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>


void	free_all_memory(t_leaks *heap);

t_leaks *leaks_collector(void *for_leaks, t_leaks *heap);

/* ft_ malloc that i will use to allocate mamory */

void *ft_malloc(size_t size, t_leaks **heap);

char	*get_type_token(char **spl, char *type, int s, t_leaks **heap);

char	*ft_dup_str(const char *s1, t_leaks **heap)
{
	int		i;
	char	*str;

	i = ft_strlen(s1);
	str = ft_malloc((i + 1) * sizeof(char), heap);
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

static int	count_str(char const *str, char c)
{
	int	i;
	int	leng;

	i = 0;
	leng = 0;
	while (str[i] != 0)
	{
		while (str[i] == c && str[i] != 0)
			i++;
		if (str[i] != c && str[i] != 0)
			leng++;
		while (str[i] != c && str[i] != 0)
			i++;
	}
	return (leng);
}

static int	start(char const *str, char c)
{
	int	l;

	l = 0;
	while (str[l] != 0 && str[l] == c)
		l++;
	return (l);
}

static int	endstr(char const *str, char c)
{
	int	l;

	l = 0;
	while (str[l] != 0 && str[l] != c)
		l++;
	return (l);
}

static char	*coppy(char const *str, int l, t_leaks **heap)
{
	int		i;
	char	*s1;

	i = 0;
	s1 = ft_malloc(sizeof(char) * (l + 1), heap);
	if (s1 == NULL)
		return (NULL);
	while (i < l)
	{
		s1[i] = str[i];
		i++;
	}
	s1[i] = 0;
	return (s1);
}

char	**ft_split(char const *s, char c, t_leaks **heap)
{
	int		i;
	char	**all;
	int		end;
	int		size;
	int		len;

	size = 0;
	i = 0;
	if (s == NULL)
		return (NULL);
	len = count_str(s, c);
	all = ft_malloc(sizeof(char *) * (len + 1), heap);
	if (all == NULL)
		return (NULL);
	while (i < len)
	{
		size += start(s + size, c);
		end = endstr(s + size, c);
		all[i] = coppy(s + size, end, heap);
		size += end;
		i++;
	}
	all[i] = NULL;
	return (all);
}
