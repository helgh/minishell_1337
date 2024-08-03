/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 09:44:43 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/08/03 14:06:46 by hael-ghd         ###   ########.fr       */
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
    str++;
    while (*str)
    {
		if (*str == 124)
			s[(*l)++] = -1;
        if (*str == c)
            return (++i);
		if (*str != 124)
			s[(*l)++] = *str;
        i++;
        str++;
    }
    return (-1);
}

char	*check_qoutes(char *str)
{
	int 	n;
	int 	i;
	int 	l;
	char	*s;

    i = -1;
    n = 0;
	l = 0;
	s = malloc(sizeof(char) * (ft_strlen(str) + 1));
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
			s[l++] = str[i];
    }
	s[l] = 0;
	return (s);
}

void	parsing(char *str, char **env)
{
	(void) 	env;
	char	*s;

	s = check_qoutes(str);
	if (!s)
		return (printf("Error qoutes!\n"), exit (1));
	else
		printf("%s\n", s);

	
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