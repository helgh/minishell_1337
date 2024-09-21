/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 23:03:37 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/09/22 00:13:08 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	put_str(char *str, int fd)
{
	int	i;

	i = -1;
	if (!str)
		return ;
	write(fd, "M_H: ", 5);
	while (str[++i])
		write(fd, &str[i], 1);
	write(2, ": ", 2);
}

int	check_red_fd(t_parse *data, t_exec *ex, int flag)
{
	int	i;

	i = -1;
	if (ex->check_flag == -1 && flag == 1)
		data->exit_status = 1;
	if (ex->check_flag == -1)
		return (1);
	if (ex->herdoc)
	{
		ex->red_herdoc = open("/tmp/herdoc", O_RDONLY);
		if (ex->red_herdoc == -1)
		{
			put_str("file_herdoc", 2);
			perror("");
			if (flag == 1)
				data->exit_status = 1;
			return (1);
		}
		while (data->fd[++i] != -1)
			;
		data->fd[i] = ex->red_herdoc;
		data->fd[++i] = -1;
	}
	return (0);
}

static int	file_herdoc(t_exec *ex)
{
	if (ex->herdoc)
	{
		ex->red_herdoc = open("/tmp/herdoc", O_CREAT | O_TRUNC | O_RDWR, 0644);
		if (ex->red_herdoc != -1)
		{
			putstr_fd(ex->herdoc, ex->red_herdoc);
			close(ex->red_herdoc);
			return (0);
		}
		else
		{
			ex->check_flag = -1;
			putstr_fd("M_H: file_herdoc: ", 2);
			perror("");
			return (-1);
		}
	}
	return (1);
}

static int	ft_open(t_exec *ex, int *i)
{
	int	f;
	int	j;

	f = 1;
	j = *i + 1;
	if ((!ft_strcmp(ex->files[*i], ">") || !ft_strcmp(ex->files[*i], ">>"))
		&& !ft_strcmp(ex->files[j], "\1"))
		ex->red_out = open("", O_CREAT | O_TRUNC | O_RDWR, 0644);
	else if (!ft_strcmp(ex->files[*i], "<"))
	{
		ex->red_in = open(ex->files[j], O_RDONLY);
		f = 0;
	}
	else if (!ft_strcmp(ex->files[*i], ">"))
		ex->red_out = open(ex->files[j], O_CREAT | O_TRUNC | O_RDWR, 0644);
	else if (!ft_strcmp(ex->files[*i], ">>"))
		ex->red_out = open(ex->files[j], O_CREAT | O_APPEND | O_RDWR, 0644);
	if (ex->red_in == -1 || ex->red_out == -1)
	{
		ex->red_in = 0;
		ex->red_out = 1;
		ex->check_flag = -1;
		return (put_str(ex->files[j], 2), perror(""), -1);
	}
	return (f);
}

void	open_files(t_parse *data, t_exec *exec, int f)
{
	t_exec		*ex;
	int			i;
	int			l;

	ex = exec;
	l = -1;
	while (ex)
	{
		i = -1;
		file_herdoc(ex);
		while (ex->files && ex->files[++i])
		{
			f = ft_open(ex, &i);
			if (!f)
				data->fd[++l] = ex->red_in;
			else if (f == 1)
				data->fd[++l] = ex->red_out;
			else if (ex->check_flag == -1)
				break ;
			i++;
		}
		ex = ex->next;
	}
	data->fd[++l] = -1;
}
