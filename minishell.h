/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 09:42:01 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/08/04 15:54:45 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINISHELL_H
#define	MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
typedef enum e_type
{
	CMD,
	OPTION,
	IN_FILE,
	OUT_FILE,
	RED_IN,
	RED_OUT,
	HERDOC,
	APPEND,
	SPACE,

} s_type;
typedef struct s_token
{
	char *str;
	enum type;

} t_token;

typedef struct	s_cmd
{
	char *str;
	t_token line[1024];
	t_cmd *next;
}	t_cmd;

char	**ft_split(char const *s, char c);

#endif
