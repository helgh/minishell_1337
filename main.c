/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 09:44:43 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/08/24 12:55:10 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*global_env(void *var, void *value, int operation, t_env *env)
{
	void			*ret;
	static int		i;
	int				t;

	t = 0;
	if (operation == INIT)
	{
		env[i].var = var;
		env[i].value = value;
		i++;
	}
	else if (operation == GET)
		return (ret = env, ret);
	else if (operation == ADD)
	{
		env[i].var = var;
		env[i].value = value;
		env[i + 1].var = NULL;
		i++;
	}
	else if (operation == SET)
	{
		while (t < i && ft_strcmp(env[t].var, var) != 0)
			t++;
		env[t].value = value;
	}
	return (NULL);
}

void	init_env(char **env, t_parse *data)
{
	int i = 0;
	char **spl;

	spl = ft_split(env[i], '=', '=', &data->heap);
	global_env(spl[0], spl[1], INIT, data->envir);
	i++;
	while (env[i])
	{
		spl = ft_split(env[i], '=', '=', &data->heap);
		global_env(spl[0], spl[1], ADD, data->envir);
		i++;
	}
}

void	print_error(int flag, char *str)
{
	if (flag == F_ALLOC)
	{
		printf("M_H: Failed allocation!\n");
		exit(1);
	}
	else if (flag == S_ERROR)
		printf("M_H: syntax error near unexpected token `newline'\n");
	else if (flag == NSFOD)
		printf("M_H: %s: No such file or directory\n", str);
	else if (flag == U_QOUTE)
		printf("Error: Unclosed qoutes!\n");
	else if (flag == EXIT)
	{
		printf("exit\n");
		exit(1);

	}
}

int	cmp_str(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (1) ;
	while (str[++i] && (str[i] == 32 || str[i] == '\t'))
		;
	if (!ft_strncmp(&str[i], "exit", 4))
		if (!str[i + 4] || str[i + 4] == 32 || str[i + 4] == '\t')
			return (0);
	return (1);
}

int	count(t_parse *data, t_cmd_info *cmd, int flag)
{
	char		*type;
	int			i;
	int			nb;
	int			nb_files;
	t_tokens	*tok;

	i = -1;
	nb = 0;
	nb_files = 0;
	(void) data;
	tok = cmd->token;
	while (++i < cmd->nbr_token)
	{
		type = tok->type;
		if (!ft_strcmp(type, "cmd") || !ft_strcmp(type, "option") 
				|| !ft_strcmp(type, "arg") || !ft_strcmp(type, "delim"))
			nb++;
		else
			nb_files++;
		tok = tok->next;
	}
	if (flag == 0)
		return (nb);
	return (nb_files);
}

char	**div_arg(t_cmd_info *cmd, char **spl)
{
	int			i;
	int			s;
	t_tokens	*tok = NULL;

	i = 0;
	s = 0;
	tok = cmd->token;
	while (tok)
	{
		if (!ft_strcmp(tok->type, "cmd") && i == 0)
			i = 1;
		else if (!ft_strcmp(tok->type, "cmd") || !ft_strcmp(tok->type, "option")
				|| !ft_strcmp(tok->type, "arg") || !ft_strcmp(tok->type, "delim"))
			spl[s++] = tok->str;
		tok = tok->next;
	}
	spl[s] = NULL;
	return (spl);
}

char	**cmd_opt_arg(t_parse * data, t_cmd_info *cmd, int len)
{
	t_tokens	*tok;
	char		**spl;
	char		**str;

	if (len == 0)
		return (NULL);
	spl = ft_malloc(sizeof(char *) * (len + 1), &data->heap);
	tok = cmd->token;
	while (tok)
	{
		if (!ft_strcmp(tok->type, "cmd"))
		{
			spl[0] = tok->str;
			break ;
		}
		tok = tok->next;
	}
	str = spl + 1;
	str = div_arg(cmd, str);
	return (spl);
}

void	add_to_next(t_exec **lst, t_exec *new)
{
	t_exec	*ptr;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	ptr = *lst;
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = new;
}

char	**files(t_parse *data, t_cmd_info *cmd, int len)
{
	t_tokens	*tok;
	char		**spl;
	int			i;

	i = -1;
	if (len == 0)
		return (NULL);
	spl = ft_malloc(sizeof(char *) * (len + 1), &data->heap);
	tok = cmd->token;
	while (tok)
	{
		if (!ft_strcmp(tok->str, "<") || !ft_strcmp(tok->str, ">")
				|| !ft_strcmp(tok->str, ">>"))
			spl[++i] = tok->str;
		else if (!ft_strcmp(tok->type, "in_file") || !ft_strcmp(tok->type, "out_file")
				|| !ft_strcmp(tok->type, "app_file"))
			spl[++i] = tok->str;
		tok = tok->next;
	}
	spl[++i] = NULL;
	return (spl);
}

t_exec	*ready_for_exec(t_parse *data)
{
	t_cmd_info	*cmd;
	t_exec		*exec;
	t_exec		*tmp;
	int			i;

	cmd = data->cmd_info;
	i = -1;
	exec = NULL;
	while (++i < data->nbr_cmd)
	{
		tmp = ft_malloc(sizeof(t_exec), &data->heap);
		tmp->cmd = cmd_opt_arg(data, cmd, count(data, cmd, 0));
		tmp->files = files(data, cmd, count(data, cmd, 1));
		tmp->next = NULL;
		add_to_next(&exec, tmp);
		cmd = cmd->next;
	}
	return (exec);
}

t_exec	*parsing(char *str, t_parse *data_info)
{
	t_exec	*exec;

	if (!check_if_only_space_and_tab(str))
		return (NULL);
	if (!check_qoutes(str, length_line(str), data_info))
		return (NULL);
	if (!split_and_replace(data_info))
		return (print_error(F_ALLOC, NULL) ,NULL);
	if (!cmd_info_struct(data_info))
		return (print_error(F_ALLOC, NULL), NULL);
	if (!check_syntax_error(data_info))
		return (print_error(S_ERROR, NULL), NULL);
	expantion(data_info);
	expand_herdoc(data_info);
	exec = ready_for_exec(data_info);
	return (exec);
}

void	parsing_part(t_parse *data)
{
	// int s;
	t_cmd_info	*cmd;
	t_exec		*tok;
	signal_loop();
	while (1)
	{
		data->cmd_info = NULL;
		data->r_line = readline("\033[0;31mM_H$\033[0m ");
		if (!data->r_line || !cmp_str(data->r_line))
			return (free(data->r_line));
		tok = parsing(data->r_line, data);
		if (*data->r_line)
			add_history(data->r_line);
		cmd = data->cmd_info;
		// while (tok)
		// {
		// 	s = -1;
		// 	printf("cmd = ");
		// 	while (tok->cmd && tok->cmd[++s])
		// 		printf("%s ", tok->cmd[s]);
		// 	s = -1;
		// 	printf("\nfiles = ");
		// 	while (tok->files && tok->files[++s])
		// 		printf("%s ", tok->files[s]);
		// 	printf("\n");
		// 	tok = tok->next;
		// }
		free(data->r_line);
		// execution_part(data);
	}
}

t_parse	*init_struct(char **envp, t_env *env)
{
	t_parse	*data_info;

	data_info = malloc(sizeof(t_parse));
	if (!data_info)
		return (print_error(F_ALLOC, NULL), NULL);
	data_info->heap = NULL;
	data_info->exit_status = 0;
	data_info->envir = env;
	init_env(envp, data_info);
	return (data_info);
}

void	leaks(void)
{
	system("leaks -quiet minishell");
}

int	main(int ac, char **av, char **envp)
{
	t_parse	*data_info;
	static t_env	env[ARG_MAX];

	(void) av;
	(void) envp;
	atexit(leaks);
	if (ac != 1)
		exit(EXIT_FAILURE);
	data_info = init_struct(envp, env);
	if (!data_info)
		return (1);
	parsing_part(data_info);
	free_all_memory(data_info->heap);
	print_error(EXIT, NULL);
}
