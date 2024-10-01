/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 06:08:52 by mthamir           #+#    #+#             */
/*   Updated: 2024/10/01 20:44:14 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	print_msg(char *str, int l)
{
	if (l == 1)
		putstr_fd("exit\n", 2);
	putstr_fd("M_H: exit: ", 2);
	putstr_fd(str, 2);
	putstr_fd(": numeric argument required\n", 2);
	return (-1);
}

int	check_status(char *str, int l)
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
		putstr_fd("exit\n", 2);
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

	if (ft_strstrlen(spl) == 1)
	{
		putstr_fd("exit\n", 2);
		close(data->out);
		return (close_files(data), free_and_exit(data, data->exit_status), 0);
	}
	if (ft_strstrlen(spl) > 1 && check_if_digit(spl[1]))
	{
		putstr_fd("M_H: exit: ", 2);
		putstr_fd(spl[1], 2);
		putstr_fd(": numeric argument required\n", 2);
		c = 255;
		return (close(data->out), close_files(data), free_and_exit(data, c), 0);
	}
	else if (ft_strstrlen(spl) == 2 && !check_if_digit(spl[1]))
	{
		c = check_status(spl[1], l);
		return (close(data->out), close_files(data), free_and_exit(data, c), 0);
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
