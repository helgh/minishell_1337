/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 02:10:41 by mthamir           #+#    #+#             */
/*   Updated: 2024/08/31 02:38:13 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int check_export_parse(char *str)
{
	int i = 0;

	if (str[0] >= '0' && str[0] <= '9')
		return (1);
	while (str[i+1])
	{
		if (!ft_isalnum(str[i]))
			return (1);
		i++;
	}
	if (str[i] != '+')
		if (!ft_isalnum(str[i]))
			return (1);
	return (0);
}

void	export_with_value(char *str, t_parse *data)
{
	char **spl;

	spl = spl_msh(str, '=', &data->heap);
	if(check_append(&spl[0]))
	{
		if(!already_exist(spl[0], data))
			append_value(spl[0], spl[1], data);
		else
			add_to_env(spl[0], "=", spl[1], data);
	}
	else if (!already_exist(spl[0], data))
	{
		if (!spl[1])
			return;
		else
			set_var_to_env(spl[0], "=", spl[1], data);
	}
	else
	{
		if(!spl[1])
			add_to_env(spl[0], "=", NULL, data);
		else
			add_to_env(spl[0], "=", spl[1], data);
	}
}

void _export_vars(char **str, t_parse *data)
{
	int i;

	i = 1;
	while (str[i])
	{
		if (check_export_parse(str[i]))
			printf("M_H: export: %s : not a valid identifier\n", str[i]);
		else
		{
			if (with_egal(str[i]))
				export_with_value(str[i], data);
			else
			{
				if (!already_exist(str[i], data))
					return ;
				else
					add_to_env(str[i], NULL, NULL, data);
			}
		}
		i++;
	}
}

void	_export(char **str, t_parse *data)
{
	char	**spl;

	if (!str[1])
		print_export(1, data);
	else
		_export_vars(str, data);
}