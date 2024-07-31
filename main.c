/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 22:39:25 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/07/30 09:28:41 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse(char *str)
{
	char	**spl;
	int		i;

	i = 0;
	spl = ft_split(str, 32);
	while (*(spl++) != NULL)
	{
		// if_is_valid(*spl);
	}
}

int main(int ac, char **av, char **envp)
{
	char *prompt;

	(void) av;
	(void) envp;
	if (ac != 1)
		exit(1);
	while (1)
	{
		prompt = readline("\033[0;31mM_H$\033[0m ");
		if(!ft_strcmp("exit", prompt))
			return (printf("exit\n"), exit(1), 1);
		add_history(prompt);
		if (prompt)
		{
			// printf()
			// parse(prompt);
			// execution(prompt);
		}
		free(prompt);
	}
	return (0);
}