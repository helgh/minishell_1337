/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 02:11:03 by mthamir           #+#    #+#             */
/*   Updated: 2024/09/20 00:54:51 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	putstr_fd(char *str, int fd)
{
	int	i;

	i = -1;
	if (!str)
		return ;
	while (str[++i])
		write(fd, &str[i], 1);
}

static int	check_n_option(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (-1);
	if (str[++i] != '-')
		return (1);
	while (str[++i] == 'n')
		;
	if (str[i] == 0)
		return (2);
	return (1);
}

int	ft_echo(char **str)
{
	int	i;
	int	j;
	int	newline;

	newline = 1;
	j = 0;
	if (!str[1])
		return (ft_putstr("\n"), 0);
	while (str[++j] && check_n_option(str[j]) != 1)
		;
	i = j;
	if (i > 1)
		newline = 0;
	while (str[i] && i != -1)
	{
		ft_putstr(str[i++]);
		if (str[i])
			ft_putstr(" ");
	}
	if (newline)
		ft_putstr("\n");
	return (0);
}
