/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 09:42:01 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/08/16 04:31:47 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINISHELL_H
#define	MINISHELL_H

#include "libft_mini_shell/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
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

// typedef struct s_leaks t_leaks;
typedef struct s_leaks
{
	void			*adress;
	void			*t_struct;
	struct s_leaks 	*next;
}				t_leaks;

typedef struct	s_tokens
{
  char				*str;
  char				*type;
  int				type_qoute;
  bool				sign_dollar;
  struct s_tokens	*next;
}				t_tokens;

typedef struct	s_cmd_info
{
	char				*cmd_line;
	char				**all_token;
	int					nbr_token;
	struct s_cmd_info	*next;
}				t_cmd_info;

typedef struct	s_parse
{
	char		*line;
	char		**all_cmd;
	int			nbr_cmd;
	int			exit_status;
	t_cmd_info	*cmd_info;
	t_leaks		*heap;
	t_tokens	*token;
}				t_parse;

char	**ft_split(char const *s, char c, t_leaks **heap);
char	*ft_dup_str(const char *s1, t_leaks **heap);
char	*i_to_a(int n, t_leaks **heap);

#endif
