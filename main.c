/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 09:44:43 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/09/12 23:11:12 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_and_exit(t_parse *data)
{
	if (data->heap)
		free_all_memory(data->heap);
	if (data->heap_env)
		free_all_memory(data->heap_env);
	if (data->r_line)
		free(data->r_line);
	if (data)
		free(data);
	exit (EXIT_FAILURE);
}

void	print_error(t_parse * data, int flag)
{
	if (flag == F_ALLOC)
	{
		putstr_fd("M_H: Failed allocation!\n", 2);
		free_and_exit(data);
	}
	else if (flag == S_ERROR)
		putstr_fd("M_H: syntax error near unexpected token `newline'\n", 2);
	else if (flag == U_QOUTE)
		putstr_fd("Error: Unclosed qoutes!\n", 2);
	else if (flag == MAX_HER)
	{
		putstr_fd("M_H: maximum here-document count exceeded\n", 2);
		free_and_exit(data);
	}
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;
	char	*tofind;

	i = 0;
	str = (char *) haystack;
	tofind = (char *) needle;
	if (tofind[i] == 0)
		return (str);
	while (i < len && str[i] != 0)
	{
		j = 0;
		while (str[i + j] == tofind[j] && (i + j) < len)
		{
			if (tofind[j + 1] == 0)
				return (str + i);
			j++;
		}
		i++;
	}
	return (0);
}

t_parse	*init_struct(char **envp)
{
	t_parse	*data_info;

	data_info = malloc(sizeof(t_parse));
	if (!data_info)
		return (putstr_fd("M_H: Failed allocation!\n", 2), NULL);
	data_info->envir = NULL;
	data_info->heap = NULL;
	data_info->heap_env = NULL;
	data_info->env = NULL;
	data_info->exit_status = 0;
	data_info->flag = 0;
	init_env(envp, data_info);
	return (data_info);
}

int	check_red_fd(t_parse *data, t_exec *ex)
{
	int	i;

	i = -1;
	if (ex->check_flag == -1)
		return (1);
	if (ex->herdoc)
	{
		ex->red_herdoc = open("/tmp/herdoc", O_RDONLY);
		if (ex->red_herdoc == -1)
		{
			putstr_fd("file_herdoc", 2);
			perror("");
			return (1);
		}
		while (data->fd[++i] != -1)
			;
		data->fd[i] = ex->red_herdoc;
		data->fd[++i] = -1;
	}
	return (0);
}

char	*path_env(char **envp)
{
	char	*envir;

	while (ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	envir = ft_strnstr(*envp, "/", 6);
	return (envir);
}

int		execute_cmd(char **cmd, char *path, char **envp)
{
	if (execve(path, cmd, envp))
		printf("error");
	return (0);
}

int		check_slash(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '/')
			return (1);
	}
	return (0);
}

int		check_access(t_parse *data, t_exec *ex)
{
	char	**spl_env;
	char	**s;
	char	*path;

	spl_env = ft_split(path_env(data->env), ':', ':', data);
	s = spl_env;
	path = ex->cmd[0];
	while (!check_slash(ex->cmd[0]) && *(spl_env++) != NULL)
	{
		*spl_env = ft_strjoin(*spl_env, "/", data);
		path = ft_strjoin(*spl_env, ex->cmd[0], data);
		if (access(path, F_OK | X_OK) == -1 && *(spl_env + 1) == NULL)
		{
			putstr_fd("M_H: ", 2);
			putstr_fd(ex->cmd[0], 2);
			putstr_fd(": command not found\n", 2);
			return (-1);
		}
		else if (access(path, F_OK | X_OK) != -1)
			break ;
	}
	execute_cmd(ex->cmd, path, data->env);
	return (0);
}

int	arg_env(char **cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (ft_strcmp(cmd[i], "env"))
		{
			putstr_fd("env: ", 2);
			putstr_fd(cmd[i], 2);
			putstr_fd(": No such file or directory\n", 2);
			return (1);
		}
	}
	return (0);
}

void	dup_files(t_exec *ex, int i, int *pipe_fd)
{
	close(pipe_fd[0]);
	if (ex->red_out == 1 && i == 0)
		dup2(pipe_fd[1], STDOUT_FILENO);
	else
		dup2(ex->red_out, STDOUT_FILENO);
	close(pipe_fd[1]);
}

int	check_if_builtin(t_parse *data, t_exec *ex)
{
	(void) data;
	if (!ft_strcmp(ex->cmd[0], "env"))
		return (0);
	else if (!ft_strcmp(ex->cmd[0], "export"))
		return (0);
	return (1);
}

void	exec_builtin(t_parse *data, t_exec *ex, int i, int *pipe_fd)
{
	dup_files(ex, i, pipe_fd);
	if (!ft_strcmp(ex->cmd[0], "env"))
	{
		if (!arg_env(ex->cmd))
			print_env(data);
	}
	// else if (!ft_strcmp(ex->cmd[0], "export"))
	// 	_export(ex->cmd, data);
}

void	child_process(t_parse *data, t_exec *ex, int i, int *pipe_fd)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return ;
	else if (pid == 0)
	{
		if (ex->red_herdoc)
			dup2(ex->red_herdoc, 0);
		else if (ex->red_in)
			dup2(ex->red_in, 0);
		dup_files(ex, i, pipe_fd);
		check_access(data, ex);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
	}
}

void	_exec(t_parse *data, t_exec *ex, int i)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (print_error(data, F_ALLOC));
	// if (!check_if_builtin(data, ex))
	// 	exec_builtin(data, ex, i, pipe_fd);
	// else
	child_process(data, ex, i, pipe_fd);
}

void	execution_part(t_parse *data, t_exec *exec)
{
	t_exec	*ex;
	int		i;
	int		flag;
	int		std_in;

	i = -1;
	ex = exec;
	flag = 0;
	open_files(data, exec);
	std_in = dup(STDIN_FILENO);
	data->env = l_list_to_array(data);
	while (++i < data->nbr_cmd)
	{
		if (i == data->nbr_cmd - 1)
			flag = 1;
		if (!check_red_fd(data, ex))
			_exec(data, ex, flag);
		ex = ex->next;
	}
	while (wait(NULL) != -1)
		;
	dup2(std_in, STDIN_FILENO);
	close (std_in);
}

t_exec	*parsing_part(char *str, t_parse *data_info)
{
	t_exec	*exec;

	if (!check_if_only_space_and_tab(str))
		return (NULL);
	if (!check_qoutes(str, length_line(str), data_info))
		return (NULL);
	if (!split_and_replace(data_info))
		return (NULL);
	if (!cmd_info_struct(data_info))
		return (NULL);
	expantion(data_info);
	checker_herdoc(data_info);
	if (max_herdoc(data_info))
		return (print_error(data_info, MAX_HER), NULL);
	expand_herdoc(data_info);
	if (!check_syntax_error(data_info))
		return (print_error(data_info, S_ERROR), NULL);
	exec = ready_for_exec(data_info);
	return (exec);
}

void	minishell(t_parse *data)
{
	t_exec		*exec;

	while (1)
	{
		signal_loop();
		data->cmd_info = NULL;
		data->r_line = readline("\033[0;31mM_H$\033[0m ");
		if (!data->r_line)
			return (free_and_exit(data));
		exec = parsing_part(data->r_line, data);
		if (exec)
			execution_part(data, exec);
		if (*data->r_line)
			add_history(data->r_line);
		free(data->r_line);
		free_all_memory(data->heap);
		data->heap = NULL;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_parse	*data_info;

	(void) av;
	if (ac != 1)
		exit(EXIT_FAILURE);
	data_info = init_struct(envp);
	if (!data_info)
		return (1);
	minishell(data_info);
	// free (data_info);
}
