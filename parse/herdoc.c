/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 12:44:54 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/08/31 02:06:17 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*read_herdoc(t_parse *data, char *str, int flag)
{
	char	*line;
	char	*new_line;
	char	*herdoc;

	herdoc = ft_dup_str("", &data->heap);
	signal_herdoc();
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(str, line))
			return (free(line), ft_restore_input(), herdoc);
		new_line = ft_strjoin(line, "\n", &data->heap);
		free (line);
		if (*data->r_line)
			add_history(data->r_line);
		if (flag != 0)
			herdoc = ft_strjoin(herdoc, new_line, &data->heap);
		else
			herdoc = ft_strjoin(herdoc, set_value(data, new_line, &data->heap), &data->heap);
	}
	return (herdoc);
}
