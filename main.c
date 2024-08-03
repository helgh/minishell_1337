/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 09:44:43 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/08/03 18:12:26 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	ft_strlen(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

int     s_d_qoutes(char *str, char *s, int *l)
{
    int     i;
    char    c;

    i = 0;
    c = *str;
	s[(*l)++] = c;
    str++;
    while (*str)
    {
		if (*str == 124)
			s[(*l)++] = -1;
        if (*str == c)
		{
			s[(*l)++] = c;
            return (++i);
		}
		if (*str != 124)
			s[(*l)++] = *str;
        i++;
        str++;
    }
    return (-1);
}

void	space_between_oper(char *str, char *s, int *i, int *l)
{
	while (str[*i] && str[*i] != 34 && str[*i] != 39)
	{
		if (str[*i] == 124 || str[*i] == 60 || str[*i] == 62)
		{
			s[(*l)++] = 32;
			s[(*l)++] = str[*i];
			if (str[*i] != str[*i + 1])
				s[(*l)++] = 32;
			else
			{
				s[(*l)++] = str[*i];
				(*i)++;
				s[(*l)++] = 32;
			}
		}
		else
			s[(*l)++] = str[*i];
		(*i)++;
	}
}

char	**check_qoutes(char *str, int len)
{
	int 	n;
	int 	i;
	int 	l;
	char	*s;

    i = -1;
    n = 0;
	l = 0;
	s = malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	while (str[++i])
    {
		if (str[i] == '\"' || str[i] == '\'')
		{
            n = s_d_qoutes(&str[i], s, &l);
        	if (n == -1)
            	return (free(s), NULL);
        	else
            	i += n;
		}
		else
			space_between_oper(str, s, &i, &l);
    }
	return (s[l] = 0, printf("%s\n", s), ft_split(s, 124));
}

int		length_line(char *str)
{
	int	i;
	int	n;

	i = -1;
	n = 0;
	while (str[++i])
	{
		if (str[i] == 124)
			n++;
		else if (str[i] == 60)
		{
			if (str[i + 1] == 60)
				i++;
			n++;
		}
		else if (str[i] == 62)
		{
			if (str[i + 1] == 62)
				i++;
			n++;
		}
	}
	n = ft_strlen(str) + (n * 2);
	return (n);
}

void	parsing(char *str, char **env)
{
	(void) 	env;
	char	**s;
	int		len;

	len = length_line(str);
	s = check_qoutes(str, len);
	if (!s)
		return (printf("Error qoutes!\n"), exit (1));
	// while (*s)
	// {
	// 	printf("%s\n", *s);
	// 	s++;
	// }

	
}

int main(int ac, char **av, char **envp)
{
	char	*line;

	(void) av;
	(void) envp;
	if (ac != 1)
		exit(EXIT_FAILURE);
	rl_readline_name = "myshell";
	while (1)
	{
		line = readline("\033[0;31mM_H$\033[0m ");
		if (!strcmp(line, "exit"))
			return (printf("exit\n"), 1);
		parsing(line, envp);
		if (*line)
			add_history(line);
		free(line);
	}
}