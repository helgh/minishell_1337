/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 23:03:37 by hael-ghd          #+#    #+#             */
/*   Updated: 2024/09/12 01:20:54 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

	f = 1;
	if (!ft_strcmp(ex->files[*i], "<"))
	{
		ex->red_in = open(ex->files[*i + 1], O_RDONLY);
		f = 0;
	}
	else if (!ft_strcmp(ex->files[*i], ">"))
		ex->red_out = open(ex->files[*i + 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
	else if (!ft_strcmp(ex->files[*i], ">>"))
		ex->red_out = open(ex->files[*i + 1], O_CREAT | O_APPEND | O_RDWR, 0644);
	if (ex->red_in == -1 || ex->red_out == -1)
	{
		ex->check_flag = -1;
		put_str(ex->files[*i + 1], 2);
		perror("");
		return (-1);
	}
	return (f);
}

void	open_files(t_parse *data, t_exec *exec)
{
	t_exec		*ex;
	int			i;
	int			l;
	int			f;

	ex = exec;
	l = -1;
	f = 0;
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
			i++;
		}
		ex = ex->next;
	}
	data->fd[++l] = -1;
}
