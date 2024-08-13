/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 09:44:43 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/08/13 06:18:43 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_leaks *leaks_collector(void *for_leaks, int operation)
{
	static t_leaks	*catch_leaks;
	static t_leaks	*head;
	t_leaks	*new;
	static size_t	i;

	if (operation == ADD)
	{
		new = malloc(sizeof(t_leaks));
		if (!new)
			return (NULL);
		new->adress = for_leaks;
		new->next = NULL;
		if (i == 0)
		{
			catch_leaks = new;
			head = catch_leaks;
		}
		else
		{
			catch_leaks->next = new;
			catch_leaks = catch_leaks->next;
		}
		i++;
	}
	if (operation == GET)
		return (head);
	return (NULL);
}
/* ft_ malloc that i will use to allocate mamory */

void *ft_malloc(size_t size)
{
	char	*new;
	new = malloc (size);
	if (!new)
		exit(EXIT_FAILURE);
	leaks_collector(new, ADD);
	return (new);
}

int	ft_strlen(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

int     s_d_qoutes(char *str, char *s, int *l)
{
    int     i;
    char    c;

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
	int 	n;
	int 	i;
	int 	l;

    i = -1;
    n = 0;
	l = 0;
	data_info->line = ft_malloc(sizeof(char) * (len + 1));
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

int		length_line(char *str)
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
	data_info->all_cmd = ft_split(data_info->line, 124);
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

char	*get_type_token(char **spl, char *type, int s)
{
	if (!strcmp(spl[s], ">"))
		return (strdup("red_out"));
	else if (!strcmp(spl[s], "<"))
		return (strdup("red_in"));
	else if (!strcmp(spl[s], ">>"))
		return (strdup("append"));
	else if (!strcmp(spl[s], "<<"))
		return (strdup("herdoc"));
	else if (s > 0 && !strcmp(spl[s - 1], ">"))
		return (strdup("out_file"));
	else if (s > 0 && !strcmp(spl[s - 1], "<"))
		return (strdup("in_file"));
	else if (s > 0 && !strcmp(spl[s - 1], "<<"))
		return (strdup("delim"));
	else if (s > 0 && !strcmp(spl[s - 1], ">>"))
		return (strdup("app_file"));
	else if (s == 0 || !strcmp(type, "delim") || !strcmp(type, "in_file"))
		return (strdup("cmd"));
	return (strdup("arg"));
}

t_tokens	*tokens_struct(t_cmd_info *info, int s)
{
	int		i;
	char	*type;

	i = -1;
	info[s].token = ft_malloc(sizeof(t_tokens) * info[s].nbr_token);
	if (!info[s].token)
		return (NULL);
	while (++i < info[s].nbr_token)
	{
		info[s].token[i].str = info[s].all_token[i];
		if (i > 0)
			type = info[s].token[i - 1].type;
		info[s].token[i].type = get_type_token(info[s].all_token, type, i);
		// printf("%s\n", info[s].token[i].type);
	}
	return (info[s].token);
}

t_cmd_info	*cmd_info_struct(t_parse *data_info)
{
	int	i;
	int	s;

	i = -1;
	data_info->cmd_info = ft_malloc((sizeof(t_cmd_info) * data_info->nbr_cmd) + 1);
	if (!data_info->cmd_info)
		return (NULL);
	while (++i < data_info->nbr_cmd)
	{
		s = -1;
		data_info->cmd_info[i].cmd_line = data_info->all_cmd[i];
		data_info->cmd_info[i].all_token = ft_split(data_info->all_cmd[i], 32);
		data_info->cmd_info[i].nbr_token = 0;
		while (data_info->cmd_info[i].all_token[++s])
			data_info->cmd_info[i].nbr_token++;
		if (!tokens_struct(data_info->cmd_info, i))
			return (NULL);
	}
	// data_info->cmd_info[i] = NULL;
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
	if (!strcmp(type, "red_in"))
		return (0);
	else if (!strcmp(type, "red_out"))
		return (0);
	else if (!strcmp(type, "append"))
		return (0);
	else if (!strcmp(type, "herdoc"))
		return (0);
	return (1);
}

int	check_syntax_error(t_parse *data)
{
	int		i;
	int		s;
	int		flag;

	i = -1;
	while (++i < data->nbr_cmd)
	{
		s = -1;
		flag = 0;
		while (++s < data->cmd_info[i].nbr_token)
		{
			if ((s + 1) == data->cmd_info[i].nbr_token)
			{
				if (check_if_operator(data->cmd_info[i].token[s].type) == 0)
					return (0);
			}
			else if (check_if_operator(data->cmd_info[i].token[s].type) == 0)
				if (check_if_operator(data->cmd_info[i].token[s + 1].type) == 0)
					return (0);
			flag = 1;
		}
		if (flag == 0)
			return (0);
	}
	return (1);
}

char	*check_dollar_sign(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[0] == '\'')
			return (strdup(str + 1));
	}
	return (NULL);
}

// void	expantion(t_parse *data)
// {
// 	int		i;
// 	int		s;
// 	char	*tmp;

// 	i = -1;
// 	while (++i < data->nbr_cmd)
// 	{
// 		s = -1;
// 		while (++s < data->cmd_info[i].nbr_token)
// 		{
// 			tmp = data->cmd_info[i].token[s].str;
// 			tmp = check_dollar_sign(tmp);
// 			tmp[ft_strlen(tmp) - 1] = 0;
// 			free (data->cmd_info[i].token[s].str);
// 			data->cmd_info[i].token[s].str = tmp;
// 			printf("%s\n", data->cmd_info[i].token[s].str);
// 		}
// 	}
// }

int	parsing(char *str, char **env, t_parse *data_info)
{
	(void) 	env;
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
	// expantion(data_info);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_parse	*data_info;

	(void) av;
	(void) envp;
	if (ac != 1)
		exit(EXIT_FAILURE);
	data_info = ft_malloc(sizeof(t_parse));
	rl_readline_name = "myshell";
	while (1)
	{
		line = readline("\033[0;31mM_H$\033[0m ");
		if (!strcmp(line, "exit"))
			return (printf("exit\n"), 1);
		parsing(line, envp, data_info);
		if (*line)
			add_history(line);
		free(line);
	}
}
