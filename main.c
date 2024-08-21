/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 09:44:43 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/08/21 15:21:50 by hael-ghd         ###   ########.fr       */
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

void init_env(char **env, t_parse *data)
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

// int	count_size(t_cmd_info *lst)
// {
// 	int			count;
// 	t_cmd_info	*ptr;

// 	count = 0;
// 	if (lst == NULL)
// 		return (0);
// 	ptr = lst;
// 	while (ptr != NULL)
// 	{
// 		count++;
// 		ptr = ptr->next;
// 	}
// 	return (count);
// }

int	parsing(char *str, char **env, t_parse *data_info)
{
	(void) env;
	if (check_if_only_space_and_tab(str) == 0)
		return (1);
	if (!check_qoutes(str, length_line(str), data_info))
		return (free(str), 1);
	if (!split_and_replace(data_info))
		return (printf("Failed allocation!\n"));
	if (!cmd_info_struct(data_info))
		return (printf("Failed allocation!\n"));
	if (check_syntax_error(data_info) == 0)
		return (printf("M_H: syntax error near unexpected token `newline'\n"));
	expantion(data_info);
	expand_herdoc(data_info);
	return (0);
}

void	leaks()
{
	system("leaks -quiet minishell");
}

int	cmp_str(char *str)
{
	int	i;

	i = -1;
	while (str[++i] && (str[i] == 32 || str[i] == '\t'))
		;
	if (!ft_strncmp(&str[i], "exit", 4))
		if (!str[i + 4] || str[i + 4] == 32 || str[i + 4] == '\t')
			return (0);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_parse	*data_info;
	static t_env	env[ARG_MAX];

	(void) av;
	(void) envp;
	if (ac != 1)
		exit(EXIT_FAILURE);
	atexit(leaks);
	data_info = malloc(sizeof(t_parse));
	data_info->heap = NULL;
	data_info->exit_status = 0;
	data_info->envir = env;
	init_env(envp, data_info);
	rl_readline_name = "myshell";
	while (1)
	{
		// data_info->token = NULL;
		data_info->cmd_info = NULL;
		data_info->r_line = readline("\033[0;31mM_H$\033[0m ");
		if (!cmp_str(data_info->r_line))
			return (free_all_memory(data_info->heap), free(data_info), free(data_info->r_line), printf("exit\n"), 1);
		parsing(data_info->r_line, envp, data_info);
		t_cmd_info *ok;
		ok = data_info->cmd_info;
		while (ok)
		{
			while (ok->token)
			{
				printf("%s -- %s\n", ok->token->type, ok->token->str);
				ok->token = ok->token->next;
			}
			ok = ok->next;
		}
		if (*data_info->r_line)
			add_history(data_info->r_line);
		free(data_info->r_line);
	}
	// free_all_memory(data_info->heap);
}
