/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:51:46 by mthamir           #+#    #+#             */
/*   Updated: 2024/08/19 16:46:00 by mthamir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINI_H
#define	MINI_H

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
#define PRINT_ENV	5
#define PRINT_EXP	6
#define APPEND		7
#define UNSET		8

typedef struct s_export t_export;
typedef struct s_export
{
	char *var;
	char *egal;
	char *value;
	t_export *next;
}	t_export;

typedef struct s_env t_env;
typedef struct s_env
{
	char *var;
	char *egal;
	char *value;
	t_env *next;
}	t_env;

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

void	init_env(char **env);
void	no_env(void);
t_env	*global_env(void	*var, void *egal, void	*value, int operation);
char	**spl_msh(char const *s, char c);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char	*s1);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strcmp(const char *s1, const char *s2);
void	add_to_env(char *var, char *egal,  char *value);
void	append_value(char *var,char *value);
void	set_var_to_env(char *var, char *value);
void	print_env();
void	print_export();
void	unset_var_from_env(char	*var);
void	append_value(char *var,char *value);
void	add_to_env(char *var, char *egal,  char *value);
int		pars_variable(char *var);
int		is_special_char(char c);
int		is_number(char c);
void	get_pwd();

#endif