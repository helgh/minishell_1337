/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthamir <mthamir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 09:42:01 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/09/18 22:56:07 by mthamir          ###   ########.fr       */
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
# include <signal.h>
# include <string.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

# define GET			1
# define SET			2
# define ADD			3
# define INIT			4
# define PRINT_ENV		5
# define PRINT_EXP		6
# define APPEND			7
# define UNSET			8

# define F_ALLOC		1
# define S_ERROR		2
# define U_QOUTE		4
# define MAX_HER		5
# define F_PIPE			6
# define F_FORK			7
# define EXIT			8



// typedef struct s_leaks t_leaks;

extern int g_int;

typedef struct s_env
{
	char			*var; /* hadi dyal */
	char			*value;
	char			*egal;
	int				index;
	struct s_env	*next;
}			t_env;

typedef struct s_leaks
{
	void			*adress;
	void			*t_struct;
	struct s_leaks	*next;
}				t_leaks;

typedef struct s_exec
{
	char			**cmd;
	char			**files;
	char			*herdoc;
	int				red_in;
	int				red_out;
	int				red_herdoc;
	int				check_flag;
	int				flag_ex;
	int				pos;
	struct s_exec	*next;
}				t_exec;

typedef struct s_tokens
{
	char				*str;
	char				*type;
	int					type_qoute;
	bool				sign_dollar;
	bool				flag_ex;
	struct s_tokens		*next;
}						t_tokens;

typedef struct s_cmd_info
{
	char				*cmd_line;
	char				**all_token;
	int					nbr_token;
	int					checker;
	t_tokens			*token;
	t_exec				*exec;
	struct s_cmd_info	*next;
}				t_cmd_info;

typedef struct s_parse
{
	char		*line;
	char		*r_line;
	char		**all_cmd;
	int			nbr_cmd;
	int			exit_status;
	int			flag;
	char		**env;
	int			fd[OPEN_MAX];
	int			*pid;
	t_env		*envir;
	t_cmd_info	*cmd_info; 
	t_leaks		*heap;
	t_leaks		*heap_env;
}				t_parse;

char		**ft_split(char const *s, char c, char c1, t_parse *data);
char		*sub_str(char *s, unsigned int start, size_t len, t_parse *data);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_dup_str(char *s1, t_parse *data);
char		*ft_strdup(char *s1, t_parse *data);
int			ft_atoi(const char *str);
char		*i_to_a(int n, t_parse *data);
char		*join_str(t_parse *data, char *str, char *s, int l);
char		*ft_strjoin(char *s1, char *s2, t_parse *data);
char		*ft_strjoin_env(char *s1, char *s2, t_parse *data);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strlen(char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
void		ft_putstr(char *str);

void		print_error(t_parse * data, int flag);
void		free_and_exit(t_parse *data, unsigned char ex);
void		free_all_memory(t_leaks *heap);

t_parse		*init_struct(char **envp);
char		*check_qoutes(char *str, int len, t_parse *data_info);
int			length_line(char *str);
void		expantion(t_parse *data);
char		*set_value(t_parse *data, char *str);
char		**split_and_replace(t_parse *data_info);
void		replace_value(char **str, int i, int *s);
int			check_if_only_space_and_tab(char *str);
int			if_operator(char *type);
char		*exp_d_quotes(t_parse *data, t_tokens *tok, int *ind, char *line);
char		*exp_s_quotes(t_parse *data, t_tokens *tok, int *ind);
char		*exp_without_quotes(t_parse *data, t_tokens *tok, int *ind);
int			sign_in_end(char *str, int *ind);
int			check_syntax_error(t_parse *data, int i);
char		*get_type_token(char **spl, char *type, int s, t_parse *data);
int			set_flag_dollar(t_tokens *token);
int			set_flag_qoutes(char *str);
t_cmd_info	*cmd_info_struct(t_parse *data_info);
t_tokens	*tokens_struct(t_cmd_info *cmd, t_parse *data);
void		checker_herdoc(t_parse *data);
int			max_herdoc(t_parse *data);
char		*set_value_2(t_parse *data, char *str);
void		expand_herdoc(t_parse *data);
char		*read_herdoc(t_parse *data, t_cmd_info *cmd, t_tokens *tok, int s);
char		*check_access(t_parse *data, t_exec *ex);
char		*exp_loop(t_parse *data, t_tokens *tok);
t_exec		*ready_for_exec(t_parse *data);
void		add_to_next(t_exec **lst, t_exec *new);
char    	**l_list_to_array(t_parse *data);

void		*ft_malloc(size_t size, t_parse *data);
void		*ft_env_malloc(size_t size, t_parse *data);
int			cmp_str(char *str, t_parse *data);
int			pars_variable(char *var);
int			is_special_char(char c);
int			is_number(char c);
void		signal_handler(int sig);
void		no_env(void);
char		**spl_msh(char *s, char c, t_parse *data);
void		signal_loop(t_parse *data);
void		ft_restore_input(void);
void		signal_herdoc(void);
void		print_error(t_parse *data, int flag);
void		signal_handler(int sig);
void		open_files(t_parse *data, t_exec *exec);
int			check_red_fd(t_parse *data, t_exec *ex, int flag);
void		dup_input(t_exec *ex);
void		dup_output(t_exec *ex, int i, int *pipe_fd);

/*_____________________________________________________________________________*/
/* builitns declaration funtions */

void	putstr_fd(char *str, int fd);
void	init_env(char **env, t_parse *data);
int		print_env(t_parse *data);
void	global_env(char **env, t_parse *data);
void	add_to_env(char *var, char *egal,  char *value, t_parse *data);
int		print_export(t_parse *data);
void	append_value(char *var,char *value, t_parse *data);
void	set_var_to_env(char *var, char *egal, char *value, t_parse *data);
int		check_export_parse(char *str, t_parse *data);
void	export_with_value(char *str, t_parse *data);
int		_export_vars(char **str, t_parse *data, int i);
int		_export(char **str, t_parse *data);
int 	cd(char **str, t_parse *data);
int		to_home(t_parse *data);
int		switch_the_old(t_parse *data);
int		to_the_root(t_parse *data);
int		same_dir(t_parse *data);
char	*get_value(char *var, t_parse *data);
void	parent_removed(char *path, t_parse *data);
int		go_to_path(char *path, t_parse *data);
void	print_cd_err(void);
int		get_pwd(void);
void	ft_exit(t_parse *data, char **cmd, t_exec *ex);
int		_unset(char **str, t_parse *data);
void	check_cmd(t_parse *data);
int		already_exist(char *var, t_parse *data);
int		ft_echo(char **str);
int		check_append(char **str);
int		with_egal(char *str);
void	increment_shlvl(t_parse *data);
void	init_index(t_parse **data);
int		sort_list(t_parse **data);
void	_exec(t_parse *data, t_exec *ex, int i);
int		arg_env(t_parse *data, char **cmd);
void	status(t_parse *data);

/*_____________________________________________________________________________*/


#endif