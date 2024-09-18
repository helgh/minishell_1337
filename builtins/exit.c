/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 06:08:52 by mthamir           #+#    #+#             */
/*   Updated: 2024/09/18 02:34:11 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_status(char *str, int l)
{
	int				i;
	int				sign;
	unsigned long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+' )
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i++] - 48);
		if (result > 9223372036854775806)
			return (print_msg(str, l));
	}
	if (l == 1)
		printf("exit\n");
	return (result * sign);
}

int	ft_strstrlen(char **str)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
		;
	return (i);
}

int	__exit_1(char **spl, t_parse *data, int l)
{
	unsigned char	c;

	if (!(*spl))
		return (1);
	if (ft_strstrlen(spl) == 1)
		return (putstr_fd("exit\n", 2), free_and_exit(data, 0), 0);
	if (ft_strstrlen(spl) > 1 && check_if_digit(spl[1]))
	{
		printf("exit\nM_H: exit: %s: numeric argument required\n", spl[1]);
		c = 255;
		free_and_exit(data, c);
	}
	else if (ft_strstrlen(spl) == 2 && !check_if_digit(spl[1]))
	{
		c = check_status(spl[1], l);
		free_and_exit(data, c);
	}
	else if (ft_strstrlen(spl) > 2 && !check_if_digit(spl[1]))
		return (putstr_fd("exit\nM_H: exit: too many arguments\n", 2), 1);
	return (0);
}

void	ft_exit(t_parse *data, char **cmd, t_exec *ex)
{
	(void) ex;
	if (data->nbr_cmd == 1)
		data->exit_status = __exit_1(cmd, data, 1);
	else
		data->exit_status = __exit_2(cmd, 0);
}
