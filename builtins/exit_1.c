/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 02:31:58 by mthamir           #+#    #+#             */
/*   Updated: 2024/09/27 22:59:32 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_digit(char *str)
{
	int	i;

	i = -1;
	if (!check_if_only_space_and_tab(str))
		return (1);
	while (str[++i])
	{
		while (str[i] == 32 || str[i] == 9)
			i++;
		while (ft_isdigit(str[i]))
			i++;
		return (check_if_only_space_and_tab(&str[i]));
	}
	return (0);
}

int	__exit_2(char **spl, int l)
{
	unsigned char	c;

	if (!(*spl))
		return (1);
	if (ft_strstrlen(spl) == 1)
		return (0);
	if (ft_strstrlen(spl) > 1 && check_if_digit(spl[1]))
	{
		putstr_fd("M_H: exit: ", 2);
		putstr_fd(spl[1], 2);
		putstr_fd(": numeric argument required\n", 2);
		return (255);
	}
	else if (ft_strstrlen(spl) == 2 && !check_if_digit(spl[1]))
	{
		c = check_status(spl[1], l);
		return (c);
	}
	else if (ft_strstrlen(spl) > 2 && !check_if_digit(spl[1]))
		return (putstr_fd("M_H: exit: too many arguments\n", 2), 1);
	return (0);
}
