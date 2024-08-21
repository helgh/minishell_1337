/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hael-ghd <hael-ghd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 20:04:13 by mthamir           #+#    #+#             */
/*   Updated: 2024/08/20 15:56:42 by hael-ghd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*________________________________________________________________________________*/
/* a function to get the current working directory */

void	get_pwd()
{
	char *cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		(printf("%s\n", cwd));
		free(cwd);
	}
	else
		perror("failed to get cwd");
}


/*________________________________________________________________________________*/
/* a function check a char if a number */

int is_number(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/*________________________________________________________________________________*/
/* a function check a char if a an alphabet */

int is_special_char(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

/*________________________________________________________________________________*/
/* function that pars the export commande variable */

int	pars_variable(char *var)
{
	int i;

	i = 1;
	if (!is_special_char(var[0]) || !is_number(var[0]))
		return(1);
	while (var[i])
	{
		if (!is_special_char(var[i]))
			return (1);
		i++;
	}
	return (0);
}

/*________________________________________________________________________________*/
 /* function to creat envirmet if the flag env -i used in the beginning and the env is NULL*/

void	no_env(t_parse *data)
{
	char	*cwd;
	int		i;

	i = 3;
	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (!cwd)
		printf("its error ");
	while (i > 0)
	{
		
	global_env("PWD", ft_strdup(cwd), "=", INIT);
	global_env("SHLVL", "1", "=",ADD);
	global_env("_", "/usr/bin/./minishell","=", ADD);
}

/*________________________________________________________________________________*/
/* function that initializ the envirement at first of the programme */

void init_env(char **env, t_parse *data)
{
	if (!env)
		no_env(data->envir);
	global_env(env, data, INIT);
	// spl = spl_msh(env[i], '=', &data->heap);
	// global_env(spl[0], "=",spl[1], INIT);
	// i++;
	// while (env[i])
	// {
	// 	spl = spl_msh(env[i], '=', &data->heap);
	// 	global_env(spl[0], "=",spl[1], ADD);
	// 	i++;
	// }
}
/*________________________________________________________________________________*/
/* function used to add a variable to the envirement "export var=value" */


void	add_to_env(char *var, char *egal,  char *value)
{
	t_env *env = global_env(NULL, NULL, NULL,  GET);
	t_env *new;
	
	if(!pars_variable(var))
		printf("syntax error");
	while (env->next)
		env = env->next;
	new = malloc(sizeof(t_env));
	new->var = var;
	new->egal = egal;
	new->value = value;
	new->next = NULL;
	env->next = new;
	env = env->next;
}

/*________________________________________________________________________________*/
/*function used when i wnat to join a value to the value of an existed variable "export var+=value"*/

void append_value(char *var,char *value)
{
	t_env *env = global_env(NULL, NULL, NULL, GET);

	while (env->next && ft_strcmp(env->var, var))
		env = env->next;
	env->value = ft_strjoin(env->value, value);
}

/*________________________________________________________________________________*/
/* function used to change the value of an existed variable in the envirement "export var=value" */

void set_var_to_env(char *var, char *value)
{
	t_env *env = global_env(NULL, NULL, NULL, GET);

	while (env->next && ft_strcmp(env->var, var))
		env = env->next;
	env->value = value;
}

/*________________________________________________________________________________*/
/* function used to print the envirement when the env commande is used  "env"*/

void print_env()
{
	t_env *env = global_env(NULL, NULL, NULL, GET);

	while (env)
	{
		if (env->egal)
			printf("%s%s%s\n", env->var, env->egal, env->value);
		env = env->next;
	}
}

/*________________________________________________________________________________*/
/* function to printf the envirement when the ""export"" commande is used */

void print_export()
{
	t_env *env = global_env(NULL, NULL, NULL, GET);

	while (env)
	{
		printf("declare -x %s", env->var);
		if (env->egal)
			printf("%s%s", env->egal, env->value);
		printf("\n");
		env = env->next;
	}
}

/*________________________________________________________________________________*/
/* function used to unset a variable from the envirment "unset var"*/

void	unset_var_from_env(char	*var)
{
	t_env *tmp;
	t_env *tmp1;
	t_env *env = global_env(NULL, NULL, NULL, GET);

	if (!pars_variable(var))
		printf("syntax error");
	while (env->next && ft_strcmp(env->next->var, var))
		env = env->next;
	if (!env)
		return ;
	if (!ft_strcmp(env->next->var, var))
	{
		tmp = env;
		tmp1 = tmp->next;
		tmp1->next = NULL;
		env = env->next->next;
		tmp->next = env;
		free(tmp1);
	}
}
/*________________________________________________________________________________*/
/*function for the globale envirement to be used wherever i want*/

t_env	*global_env(char **env, t_parse *data, int opeation)
{
	int i = 0;
	t_env	*env;
	t_env	*head;

	if (operation == INIT)
	{
		while (env[i])
		{
			if (i == 0)
			{
				env = ft_malloc(sizeof(t_env), &data->heap);
				head = env;
			}
			slp = spl_msh(env[i], '=', &data->heap);
			env->var = spl[0];
			env->egal = ft_dup_str("=", &data->heap);
			env->value = spl[1];
			env->next = NULL;
			i++
		}
	}
	else if (operation == GET)
		return (head);
	return (NULL);
}
