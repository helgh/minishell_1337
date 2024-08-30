/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 09:44:43 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/08/30 04:04:07 by hael-ghd         ###   ########.fr       */
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

int	check_if_digit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
	}
	return (0);
}

int	cmp_str(char *str, t_leaks **heap)
{
	char	**spl;
	int		i;
	int		s;

	i = -1;
	if (!str)
		return (1);
	spl = ft_split(str, 32, '\t', heap);
	while (spl[++i])
		;
	s = -1;
	if (!ft_strcmp(spl[++s], "exit"))
	{
		if (i == 1)
			return (printf("exit\n"), 0);
		if (i > 1 && check_if_digit(spl[1]))
			return (printf("exit\nM_H: exit: %s: numeric argument required\n", spl[1]), 0);
		else if (i == 2 && !check_if_digit(spl[1]))
			return (printf("exit\n"), 0);
		else if (i > 2 && !check_if_digit(spl[1]))
			return (printf("exit\nM_H: exit: too many arguments\n"), 1);
	}
	return (1);
}

void	put_str(char *str, int fd)
{
    int i;

	i = -1;
    if (!str)
        return ;
	write(fd, "M_H: ", 5);
    while (str[++i])
        write(fd, &str[i], 1);
	write(2, ": ", 2);
}

void	open_files(t_parse *data, t_exec *exec)
{
	t_exec		*ex;
	int			i;

	ex = exec;
	(void) data;
	while (ex)
	{
		i = -1;
		while (ex->files && ex->files[++i])
		{
			if (!ft_strcmp(ex->files[i], "<"))
				ex->red_in = open(ex->files[i + 1], O_RDONLY);
			else if (!ft_strcmp(ex->files[i], ">"))
				ex->red_out = open(ex->files[i + 1], O_CREAT | O_TRUNC | O_RDONLY, 0644);
			else if (!ft_strcmp(ex->files[i], ">>"))
				ex->red_out = open(ex->files[i + 1], O_CREAT | O_APPEND | O_RDONLY, 0644);
			if (ex->red_in == -1 || ex->red_out == -1)
				return (put_str(ex->files[i + 1], 2), perror(""));
		}
		ex = ex->next;
	}
}

// void	cmd_line(t_parse *data, t_exec *exec)
// {
// 	if (fork)
// }

void	execution_part(t_parse *data, t_exec *exec)
{
	int	i;

	i = -1;
	open_files(data, exec);
	// if (data->nbr_cmd == 1)
	// 	cmd_line(data, exec);
	// while (++i < data->nbr_cmd)
	// {
		
	// }
}

t_exec	*parsing_part(char *str, t_parse *data_info)
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
	expantion(data_info);
	expand_herdoc(data_info);
	if (!check_syntax_error(data_info))
		return (print_error(S_ERROR, NULL), NULL);
	exec = ready_for_exec(data_info);
	return (exec);
}

void	minishell(t_parse *data)
{
	int s;
	// t_cmd_info	*cmd;
	t_exec		*exec;

	signal_loop();
	while (1)
	{
		data->cmd_info = NULL;
		data->r_line = readline("\033[0;31mM_H$\033[0m ");
		if (!data->r_line || !cmp_str(data->r_line, &data->heap))
			return (free(data->r_line), free_all_memory(data->heap));
		exec = parsing_part(data->r_line, data);
		execution_part(data, exec);
		if (*data->r_line)
			add_history(data->r_line);
		// cmd = data->cmd_info;
		while (exec)
		{
			s = -1;
			printf("cmd = ");
			while (exec->cmd && exec->cmd[++s])
				printf("%s ", exec->cmd[s]);
			s = -1;
			printf("\nfiles = ");
			while (exec->files && exec->files[++s])
				printf("%s ", exec->files[s]);
			printf("\nherdoc = ");
			if (exec->herdoc)
				printf("%s ", exec->herdoc);
			printf("\n%d\n%d\n", exec->red_in, exec->red_out);
			exec = exec->next;
		}
		free(data->r_line);
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
	data_info->flag = 0;
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
	minishell(data_info);
	// free_all_memory(data_info->heap);
	free (data_info);
	// print_error(EXIT, NULL);
}
