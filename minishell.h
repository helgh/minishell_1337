/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 22:33:44 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/07/28 00:58:49 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>

typedef struct s_com_info
{
	char				*cmd;
	char				*valid_arg;
	int					quots;
	int					operator;
	struct s_com_info	*next;
}						t_com_info;

#endif
