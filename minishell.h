/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 09:42:01 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/08/04 16:39:24 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINISHELL_H
#define	MINISHELL_H

#include "libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#define GET		1
#define SET		2
#define ADD		3
#define INIT	4

typedef struct s_leaks
{
	char *adress;
	t_leaks *next;
}	t_leaks;


typedef struct s_env
{
	char *var;
	char *value;
}	t_env;

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
