/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 02:11:03 by mthamir           #+#    #+#             */
/*   Updated: 2024/08/30 23:52:05 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void putstr_fd(char *str, int fd)
{
	int i ;

	i = -1;
	if (!str)
		return ;
	while (str[++i])
		write(fd, &str[i], 1);
}

int	check_option(char *option)
{
	int i = 0;

	if (option[i] == '-')
		i++;
	else
		return (1);
	while (option[i])
	{
		if (option[i] == 'n')
			i++;
		else
			return (1);
	}
	return (0);
}
void ft_echo(char *str, int fd, char *option, int quot)
{
	if (option)
		if (check_option(option))
			write(1, "\n", 1);
	putstr_fd(str, fd);
}
