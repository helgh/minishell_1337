/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 06:08:52 by mthamir           #+#    #+#             */
/*   Updated: 2024/08/30 06:17:04 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    check_if_digit(char *str)
{
    int    i;

    i = -1;
    while (str[++i])
    {
        if (!ft_isdigit(str[i]))
            return (1);
    }
    return (0);
}

int    ft_exit(char **spl, t_leaks *heap)
{
    int        i;

    i = -1;
    if (!(*spl))
        return (1);
    while (spl[++i])
        ;
    if (i == 1)
        return (printf("exit\n"), 0);
	if (i > 1 && check_if_digit(spl[1]))
		return (printf("exit\nM_H: exit: %s: numeric argument required\n", spl[1]), 0);
	else if (i == 2 && !check_if_digit(spl[1]))
    	return (printf("exit\n"), 0);
    else if (i > 2 && !check_if_digit(spl[1]))
		return (printf("exit\nM_H: exit: too many arguments\n"), 1);
    return (1);
}