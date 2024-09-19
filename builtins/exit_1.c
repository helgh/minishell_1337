/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 02:31:58 by mthamir           #+#    #+#             */
/*   Updated: 2024/09/18 23:51:18 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_digit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
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
		printf("M_H: exit: %s: numeric argument required\n", spl[1]);
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
