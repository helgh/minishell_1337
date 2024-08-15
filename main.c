/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 09:44:43 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/08/15 06:46:09 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all_memory(t_leaks *heap)
{
	t_leaks	*tmp;

	while (heap && heap->next)
	{
		tmp = heap;
		heap = heap->next;
		if (tmp->adress)
		{
			free (tmp->adress);
			free (tmp->t_struct);
		}
	}
	if (heap)
	{
		free (heap->adress);
		free (heap->t_struct);
	}
}

t_leaks	*leaks_collector(void *for_leaks, t_leaks **heap)
{
	t_leaks	*tmp;
	t_leaks	*new;

	tmp = *heap;
	new = malloc(sizeof(t_leaks));
	if (!new)
		return (free_all_memory(*heap), NULL);
	new->adress = for_leaks;
	new->t_struct = new;
	new->next = NULL;
	if (!*heap)
		return (*heap = new);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (NULL);
}

/* ft_ malloc that i will use to allocate mamory */

void	*ft_malloc(size_t size, t_leaks **heap)
{
	char	*new;

	new = malloc (size);
	if (!new)
		exit(EXIT_FAILURE);
	leaks_collector(new, heap);
	return (new);
}

int	count_size(t_cmd_info *lst)
{
	int			count;
	t_cmd_info	*ptr;

	count = 0;
	if (lst == NULL)
		return (0);
	ptr = lst;
	while (ptr != NULL)
	{
		count++;
		ptr = ptr->next;
	}
	return (count);
}

int	s_d_qoutes(char *str, char *s, int *l)
{
	int		i;
	char	c;

	i = 0;
	c = *str;
	s[(*l)++] = c;
	str++;
	while (*str)
	{
		if (*str == 124)
			s[(*l)++] = -1;
		if (*str == c)
		{
			s[(*l)++] = c;
			return (++i);
		}
		if (*str != 124)
			s[(*l)++] = *str;
		i++;
		str++;
	}
	return (-1);
}

void	space_between_oper(char *str, char *s, int *i, int *l)
{
	while (str[*i] && str[*i] != 34 && str[*i] != 39)
	{
		if (str[*i] == 124 || str[*i] == 60 || str[*i] == 62)
		{
			s[(*l)++] = 32;
			s[(*l)++] = str[*i];
			if (str[*i] != str[*i + 1])
				s[(*l)++] = 32;
			else
			{
				s[(*l)++] = str[*i];
				(*i)++;
				s[(*l)++] = 32;
			}
		}
		else
			s[(*l)++] = str[*i];
		(*i)++;
	}
	*i -= 1;
}

char	*check_qoutes(char *str, int len, t_parse *data_info)
{
	int	n;
	int	i;
	int	l;

	i = -1;
	n = 0;
	l = 0;
	data_info->line = ft_malloc(sizeof(char) * (len + 1), &data_info->heap);
	if (!data_info->line)
		return (printf("Failed allocation!\n"), NULL);
	while (str[++i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			n = s_d_qoutes(&str[i], data_info->line, &l);
			if (n == -1)
				return (printf("Unclosed qoutes!\n"), free(data_info->line), NULL);
			else
				i += n;
		}
		else
			space_between_oper(str, data_info->line, &i, &l);
	}
	data_info->line[l] = 0;
	return (data_info->line);
}

int	length_line(char *str)
{
	int	i;
	int	n;

	i = -1;
	n = 0;
	while (str[++i])
	{
		if (str[i] == 124)
			n++;
		else if (str[i] == 60)
		{
			if (str[i + 1] == 60)
				i++;
			n++;
		}
		else if (str[i] == 62)
		{
			if (str[i + 1] == 62)
				i++;
			n++;
		}
	}
	n = ft_strlen(str) + (n * 2);
	return (n);
}

void	replace_value_within_quotes(char **str, int i, int *s)
{
	char	c;

	c = str[i][*s];
	while (str[i][++(*s)] && str[i][*s] != c)
	{
		if (str[i][*s] == -1)
			str[i][*s] = 124;
		else if (str[i][*s] == 32)
			str[i][*s] = -1;
	}
}

char	**split_and_replace(t_parse *data_info)
{
	int		i;
	int		s;

	i = -1;
	data_info->all_cmd = ft_split(data_info->line, 124, &data_info->heap);
	if (!data_info->all_cmd)
		return (free(data_info->line), NULL);
	data_info->nbr_cmd = 0;
	while (data_info->all_cmd[++i])
		data_info->nbr_cmd++;
	i = -1;
	while (data_info->all_cmd[++i])
	{
		s = -1;
		while (data_info->all_cmd[i][++s])
		{
			if (data_info->all_cmd[i][s] == '\'' || data_info->all_cmd[i][s] == '\"')
				replace_value_within_quotes(data_info->all_cmd, i, &s);
		}
	}
	return (data_info->all_cmd);
}

char	*get_type_token(char **spl, char *type, int s, t_leaks **heap)
{
	if (!ft_strcmp(spl[s], ">"))
		return (ft_dup_str("red_out", heap));
	else if (!ft_strcmp(spl[s], "<"))
		return (ft_dup_str("red_in", heap));
	else if (!ft_strcmp(spl[s], ">>"))
		return (ft_dup_str("append", heap));
	else if (!ft_strcmp(spl[s], "<<"))
		return (ft_dup_str("herdoc", heap));
	else if (s > 0 && !ft_strcmp(spl[s - 1], ">"))
		return (ft_dup_str("out_file", heap));
	else if (s > 0 && !ft_strcmp(spl[s - 1], "<"))
		return (ft_dup_str("in_file", heap));
	else if (s > 0 && !ft_strcmp(spl[s - 1], "<<"))
		return (ft_dup_str("delim", heap));
	else if (s > 0 && !ft_strcmp(spl[s - 1], ">>"))
		return (ft_dup_str("app_file", heap));
	else if (s == 0 || !ft_strcmp(type, "delim") || !ft_strcmp(type, "in_file"))
		return (ft_dup_str("cmd", heap));
	return (ft_dup_str("arg", heap));
}

void	add_node_to_struct(t_tokens **lst, t_tokens *new)
{
	t_tokens	*ptr;

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

t_tokens	*tokens_struct(t_parse *info, t_cmd_info *cmd, t_leaks **heap)
{
	t_tokens	*tokens;
	int			i;
	int			s;
	char		*type;

	i = -1;
	while (++i < cmd->nbr_token)
	{
		s = -1;
		tokens = ft_malloc(sizeof(t_tokens), heap);
		tokens->str = cmd->all_token[i];
		while (tokens->str[++s])
			if (tokens->str[s] == -1)
				tokens->str[s] = 32;
		tokens->type = get_type_token(cmd->all_token, type, i, heap);
		type = tokens->type;
		tokens->next = NULL;
		add_node_to_struct(&info->token, tokens);
	}
	return (info->token);
}

void	add_to_struct(t_cmd_info **lst, t_cmd_info *new)
{
	t_cmd_info	*ptr;

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

t_cmd_info	*cmd_info_struct(t_parse *data_info)
{
	t_cmd_info	*cmd;
	int			i;
	int			s;

	i = -1;
	cmd = NULL;
	while (++i < data_info->nbr_cmd)
	{
		cmd = ft_malloc(sizeof(t_cmd_info), &data_info->heap);
		s = -1;
		cmd->cmd_line = data_info->all_cmd[i];
		cmd->all_token = ft_split(data_info->all_cmd[i], 32, &data_info->heap);
		cmd->nbr_token = 0;
		cmd->next = NULL;
		while (cmd->all_token[++s])
			cmd->nbr_token++;
		tokens_struct(data_info, cmd, &data_info->heap);
		add_to_struct(&data_info->cmd_info, cmd);
	}
	return (data_info->cmd_info);
}

int	check_if_only_space_and_tab(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] != 32 && str[i] != 9)
			return (1);
	return (0);
}

int	check_if_operator(char *type)
{
	if (!ft_strcmp(type, "red_in"))
		return (0);
	else if (!ft_strcmp(type, "red_out"))
		return (0);
	else if (!ft_strcmp(type, "append"))
		return (0);
	else if (!ft_strcmp(type, "herdoc"))
		return (0);
	return (1);
}

int	check_syntax_error(t_parse *data)
{
	int			i;
	int			s;
	t_tokens	*tmp;
	t_cmd_info	*cmd;
	int			flag;

	i = -1;
	tmp = data->token;
	cmd = data->cmd_info;
	while (++i < data->nbr_cmd)
	{
		s = -1;
		flag = 0;
		while (++s < cmd->nbr_token)
		{
			if ((s + 1) == cmd->nbr_token && check_if_operator(tmp->type) == 0)
				return (0);
			else if (check_if_operator(tmp->type) == 0 && check_if_operator(tmp->next->type) == 0)
				return (0);
			flag = 1;
			tmp = tmp->next;
		}
		if (flag == 0)
			return (0);
		cmd = cmd->next;
	}
	return (1);
}

void	expantion(t_parse *data, t_tokens **token)
{
	t_tokens	*tok;

	tok = *token;
	while ()
}

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
	expantion(data_info, &data_info->token);
	return (0);
}

void	leaks()
{
	system("leaks -quiet minishell");
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_parse	*data_info;

	(void) av;
	(void) envp;
	if (ac != 1)
		exit(EXIT_FAILURE);
	atexit(leaks);
	data_info = malloc(sizeof(t_parse));
	data_info->heap = NULL;
	rl_readline_name = "myshell";
	while (1)
	{
		data_info->token = NULL;
		data_info->cmd_info = NULL;
		line = readline("\033[0;31mM_H$\033[0m ");
		if (!ft_strcmp(line, "exit"))
			return (free_all_memory(data_info->heap), free(data_info), free(line), printf("exit\n"), 1);
		parsing(line, envp, data_info);
		// while (data)
		if (*line)
			add_history(line);
		free(line);
	}
	// free_all_memory(data_info->heap);
}
