/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 00:32:48 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/09/22 17:16:08 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parse	*init_struct(char **envp)
{
	t_parse	*data_info;

	data_info = malloc(sizeof(t_parse));
	if (!data_info)
		return (putstr_fd("M_H: Failed allocation!\n", 2), NULL);
	data_info->envir = NULL;
	data_info->heap = NULL;
	data_info->heap_env = NULL;
	data_info->env = NULL;
	data_info->exit_status = 0;
	data_info->flag = 0;
	data_info->flag_spl = 0;
	init_env(envp, data_info);
	return (data_info);
}
