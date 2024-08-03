/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 09:44:43 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/08/03 10:21:51 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_qoutes(char *str)
{
	char	c;
	int		n;

	while (*(str++))
		if (*str == '\"' || *str == '\'')
			break ;
	c = *str;
	while (*(str++))
	{
		if (c == *str)
			n++;
	}
	if (n % 2 != 0)
		return (-1);
	return (0);
}

void	parsing(char *str, char **env)
{
	char	**envp;

	if (check_qoutes(str) == -1)
		exit(1);
	
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