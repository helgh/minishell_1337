/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 13:24:10 by mthamir           #+#    #+#             */
/*   Updated: 2024/08/19 16:46:31 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void check_commande(char *line)
{
	char **spl= spl_msh(line, ' ');
	char **spl2;

	if (!strcmp(spl[0], "export"))
	{
		spl2 = spl_msh(spl[1], '=');
		add_to_env(spl2[0], "=", spl2[1]);
	}
	else if (!strcmp(spl[0], "unset"))
		unset_var_from_env(spl[1]);
}

int main(int ac, char **av, char **envp)
{
	(void) ac;
	(void) av;
	init_env(envp);
	// t_env *env= global_env(NULL, NULL, NULL , GET);
	char *line = NULL;
	while (1)
	{
		line = readline("prompt :");
		if (line)
			add_history(line);
		if (!strcmp(line, "export"))
			print_export();
		else if (!strcmp(line, "env"))
			print_env();
		else if (!strcmp(line, "pwd"))
			get_pwd();
		else 
			check_commande(line);
	}
}