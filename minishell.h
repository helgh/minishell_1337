/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 09:42:01 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/08/13 06:52:49 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINISHELL_H
#define	MINISHELL_H

#include "libft_mini_shell/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#define GET			1
#define SET			2
#define ADD			3
#define INIT		4

typedef struct s_leaks t_leaks;
typedef struct s_leaks
{
	void	*adress;
	t_leaks *next;
}	t_leaks;

// typedef struct s_env
// {
// 	char *var;
// 	char *value;
// }	t_env;

// typedef enum s_type
// {
// 	CMD,
// 	OPTION,
// 	IN_FILE,
// 	OUT_FILE,
// 	RED_IN,
// 	RED_OUT,
// 	HERDOC,
// 	APPEND,
// 	LIM,
// 	ARG,
// } 	t_type;

// typedef struct s_token
// {
// 	char 		*str;
// 	enum s_type	type;
// }	t_token;

// typedef struct	s_cmd
// {
// 	char *str;
// 	t_token *line;
// }	t_cmd;

typedef struct	s_tokens
{
  char				*str;
  char				*type;
//   struct s_tokens	*next;
}				t_tokens;

typedef struct	s_cmd_info
{
	char				*cmd_line;
	char				**all_token;
	int					nbr_token;
	t_tokens			*token;
	// struct s_cmd_info	*next;
}				t_cmd_info;

typedef struct	s_parse
{
	char		*line;
	char		**all_cmd;
	int			nbr_cmd;
	t_cmd_info	*cmd_info;
}				t_parse;

char	**ft_split(char const *s, char c);

#endif
