/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 02:10:41 by mthamir           #+#    #+#             */
/*   Updated: 2024/09/18 02:46:47 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_export_parse(char *str, t_parse *data)
{
	int		i;
	char	**spl;

	i = -1;
	spl = spl_msh(str, '=', data);
	if (!spl)
		return (1);
	if (!ft_isalpha(spl[0][0]) && spl[0][0] != '_')
		return (1);
	while (spl[0][++i + 1])
	{
		if (!ft_isalnum (spl[0][i]) && (spl[0][i] != '_'))
			return (1);
	}
	if (spl[0][i] != '+')
		if (!ft_isalnum(spl[0][i]) && spl[0][i] != '_')
			return (1);
	return (0);
}

void	export_with_value(char *str, t_parse *data)
{
	char	**spl;

	spl = spl_msh(str, '=', data);
	if (spl && check_append(&spl[0]))
	{
		if (!already_exist(spl[0], data))
			append_value(spl[0], spl[1], data);
		else
			add_to_env(spl[0], "=", spl[1], data);
	}
	else if (spl && !already_exist(spl[0], data))
	{
		if (!spl[1])
			return ;
		else
			set_var_to_env(spl[0], "=", spl[1], data);
	}
	else if (spl)
		add_to_env(spl[0], "=", spl[1], data);
}

int	with_egal(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
	{
		if (str[i] == '=')
			return (1);
	}
	return (0);
}

int	_export_vars(char **str, t_parse *data, int i)
{
	int	ret;

	ret = 0;
	while (str[++i])
	{
		if (check_export_parse(str[i], data))
		{
			printf("M_H: export: %s : not a valid identifier\n", str[i]);
			ret = 1;
		}
		else
		{
			if (with_egal(str[i]))
				export_with_value(str[i], data);
			else
			{
				if (!already_exist(str[i], data))
					continue ;
				else
					add_to_env(str[i], NULL, "\0", data);
			}
		}
	}
	return (ret);
}

int	_export(char **str, t_parse *data)
{
	int	i;

	i = 0;
	if (!str[1])
		return (print_export(data));
	else
		return (_export_vars(str, data, i));
}
