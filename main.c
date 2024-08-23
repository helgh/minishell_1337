/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 09:44:43 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/08/23 15:38:07 by hael-ghd         ###   ########.fr       */
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
		printf("M_H: Failed allocation!\n");
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

void	parsing(char *str, t_parse *data_info)
{
	if (!check_if_only_space_and_tab(str))
		return ;
	if (!check_qoutes(str, length_line(str), data_info))
		return ;
	if (!split_and_replace(data_info))
		return (print_error(F_ALLOC, NULL));
	if (!cmd_info_struct(data_info))
		return (print_error(F_ALLOC, NULL));
	if (!check_syntax_error(data_info))
		return (print_error(S_ERROR, NULL));
	expantion(data_info);
	expand_herdoc(data_info);
}


void	parsing_part(t_parse *data)
{
	signal_loop();
	while (1)
	{
		data->cmd_info = NULL;
		data->r_line = readline("\033[0;31mM_H$\033[0m ");
		if (!data->r_line || !cmp_str(data->r_line))
			return (free(data->r_line));
		parsing(data->r_line, data);
		if (*data->r_line)
			add_history(data->r_line);
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

int	main(int ac, char **av, char **envp)
{
	t_parse	*data_info;
	static t_env	env[ARG_MAX];

	(void) av;
	(void) envp;
	if (ac != 1)
		exit(EXIT_FAILURE);
	data_info = init_struct(envp, env);
	if (!data_info)
		return (1);
	parsing_part(data_info);
	free_all_memory(data_info->heap);
	print_error(EXIT, NULL);
}
