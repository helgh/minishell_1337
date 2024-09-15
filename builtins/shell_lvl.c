/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_lvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:53:20 by mthamir           #+#    #+#             */
/*   Updated: 2024/09/15 03:57:05 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	increment_shlvl(t_parse *data)
{
	char	*shlvl;
	int		lvl;

	shlvl = get_value("SHLVL", data);
	if (!shlvl || !(*shlvl))
	{
		if (!already_exist("SHLVL", data))
			set_var_to_env("SHLVL", "=", "1", data);
		else
			add_to_env("SHLVL", "=", "1", data);
		return ;
	}
	lvl = ft_atoi(shlvl);
	if (lvl == 999)
	{
		set_var_to_env("SHLVL", "=", NULL, data);
		return ;
	}
	lvl++;
	shlvl = i_to_a(lvl, data);
	set_var_to_env("SHLVL", "=", shlvl, data);
	return ;
}

int	sort_list(t_parse **data)
{
	t_env	*slow;
	t_env	*fast;
	int		max;

	init_index(data);
	slow = (*data)->envir;
	fast = (*data)->envir;
	while (slow)
	{
		fast = (*data)->envir;
		while (fast)
		{
			if (ft_strcmp(slow->var, fast->var) < 0)
			{
				fast->index++;
				max = fast->index;
			}
			fast = fast->next;
		}
		slow = slow->next;
	}
	return (max);
}
