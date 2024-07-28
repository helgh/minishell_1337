/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 22:39:25 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/07/28 02:02:14 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	tokens(char *str)
// {
// 	char	**spl;
// 	int		i;

// 	i = 0;
// 	spl = ft_split(str, 32);
// 	while (*(spl++) != NULL)
// 	{
// 		if_is_valid(*spl);
// 	}
// }

int main(int ac, char **av, char **envp)
{
	char *prompt;

	if (ac != 1)
		exit(1);
	while (1)
	{
		prompt = readline("M_H$ ");
		if (prompt)
		{
			add_history(prompt);
			//tokens(prompt);
		}
		free(prompt);
	}
	return (0);
}