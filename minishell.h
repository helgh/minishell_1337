/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 09:42:01 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/08/20 14:12:13 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// #include "libft_mini_shell/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

# define GET			1
# define SET			2
# define ADD			3
# define INIT			4

// typedef struct s_leaks t_leaks;

typedef struct s_env
{
	char	*var;
	char	*value;
}			t_env;

typedef struct s_leaks
{
	void			*adress;
	void			*t_struct;
	struct s_leaks	*next;
}				t_leaks;

typedef struct s_tokens
{
	char				*str;
	char				*type;
	int					type_qoute;
	bool				sign_dollar;
	struct s_tokens		*next;
}						t_tokens;

typedef struct s_cmd_info
{
	char				*cmd_line;
	char				**all_token;
	int					nbr_token;
	t_tokens			*token;
	struct s_cmd_info	*next;
}				t_cmd_info;

typedef struct s_parse
{
	char		*line;
	char		**all_cmd;
	int			nbr_cmd;
	int			exit_status;
	t_env		*envir;
	t_cmd_info	*cmd_info;
	t_leaks		*heap;
}				t_parse;

char		**ft_split(char const *s, char c, char c1, t_leaks **heap);
char		*ft_dup_str(char *s1, t_leaks **heap);
char		*i_to_a(int n);
char		*join_str(t_parse *data, char *str, char *s, int l);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strlen(char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);

void		free_all_memory(t_leaks *heap);

char		*check_qoutes(char *str, int len, t_parse *data_info);
int			length_line(char *str);
void		expantion(t_parse *data);
char		*remove_qoutes(char *str, char c, t_leaks **heap);
char		*set_value(t_parse *data, char *str, t_leaks **heap);
char		**split_and_replace(t_parse *data_info);
void		replace_value(char **str, int i, int *s);
int			check_if_only_space_and_tab(char *str);
int			if_operator(char *type);
int			check_syntax_error(t_parse *data);
char		*get_type_token(char **spl, char *type, int s, t_leaks **heap);
int			set_flag_dollar(t_tokens *token);
int			set_flag_qoutes(char *str);
t_cmd_info	*cmd_info_struct(t_parse *data_info);
t_tokens	*tokens_struct(t_cmd_info *cmd, t_leaks **heap);

void		*ft_malloc(size_t size, t_leaks **heap);
int			cmp_str(char *str);

#endif
