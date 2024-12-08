#include<libc.h>
#include "./inc/minishell.h"

char *expand_herdoc(char *line, char **envp)
{
	int i;
	int j;
	char *env;
	char *s;
	char *tmp;
	char buff[70000];

	i = 0;
	j = 0;
	while (line[i])
	{
		j = 0;
		if (line[i] == '$')
		{
			buff[j++] = line[i++];
			while (!isalnum(line[i]) || line[i] == '_')
				buff[j++] = line[i++];
			buff[j] = 0;
			s = env_get(env, buff);
			tmp = ft_strjoin(tmp, s);
		}
		else
		{
			while (line[i] == '$')
				buff[j++] = line[i++];
			buff[j] = 0;
			tmp = ft_strjoin(tmp, buff);
		}
		
	}
	return (ft_strdup(tmp));
}
char *check_sign(char *d)
{
	int i = 0;

	if (d[i] == '$')
	{
		while (d[i] == '$')
			i++;
	}
	if ((i % 2) == 1)
		d++;
	return (d);
}

char *ft_get_delimeter(char *d, int *flag)
{
	int i;
	int j;
	char c;
	char new[500];

	i = 0;
	j = 0;
	d = check_sign(d);
	while (d[i])
	{
		if ((d[i] == '\'' || d[i] == '\"') && (*flag)++)
		{
			c = d[i++];
			while (d[i] && d[i] != c)
				new[j++] = d[i++];
			if (d[i] == c)
				i++;
		}
		else
			new[j++] = d[i++];
	}
	new[j] = 0;
	return (ft_strdup(new));
}
