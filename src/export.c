/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: Wester <Wester@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/15 19:58:50 by Wester        #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2020/06/12 16:19:13 by wbarendr      ########   odam.nl         */
=======
/*   Updated: 2020/06/12 14:06:35 by pde-bakk      ########   odam.nl         */
>>>>>>> 2348e2b2a4ac84f76ce6d66fc6dfc354e0483bc8
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		look_for_match(char **var, char *args, t_vars *p, int *i)
{
	while (p->env1[*i])
	{
		if (find_match(p->env1[*i], var[0]))
		{
			if (!(find_equal(args)))
				return (free_var_ret(var));
			if (find_equal(args) || find_equal(p->env1[*i]))
				var[0] = ft_strjoin_free(var[0], "=");
			free(p->env1[*i]);
			if (var[1] == NULL)
				p->env1[*i] = ft_strdup(var[0]);
			else
			{
				p->env1[*i] = ft_strjoin(var[0], var[1]);
				free(var[1]);
			}
			free(var[0]);
			free(var);
			return (0);
		}
		(*i)++;
	}
	return (1);
}

void	free_var(char **var, int *s)
{
	free(var[0]);
	if (var[1])
		free(var[1]);
	free(var);
	(*s)++;
}

void	create_new_var2(char **var, char **env2, t_vars *p, int i)
{
	if (var[1] == NULL)
		env2[i] = ft_strdup(var[0]);
	else
	{
		env2[i] = ft_strjoin(var[0], var[1]);
		free(var[1]);
	}
	env2[i + 1] = NULL;
	free(var[0]);
	free(var);
	i = 0;
	while (p->env1[i])
	{
		free(p->env1[i]);
		i++;
	}
	free(p->env1);
	i = 0;
	p->env1 = env2;
}

void	create_new_var(char **var, char *args, t_vars *p, int i)
{
	int		k;
	char	**env2;

	k = 0;
	if (find_equal(args))
		var[0] = ft_strjoin_free(var[0], "=");
	env2 = malloc(sizeof(char *) * (i + 2));
	if (env2 == NULL)
		exit(1);
	i = 0;
	while (p->env1[i])
	{
		env2[i] = malloc(ft_strlen(p->env1[i]) + 1);
		if (env2[i] == NULL)
			exit(1);
		while (p->env1[i][k])
		{
			env2[i][k] = p->env1[i][k];
			k++;
		}
		env2[i][k] = 0;
		k = 0;
		i++;
	}
	create_new_var2(var, env2, p, i);
}

int		export(char **args, t_vars *p)
{
	int		i;
	int		s;
	char	**var;

	s = 1;
	if (!args[1])
		return (bubble_sort(p->env1));
	while (args[s])
	{
		var = ft_split_equal(args[s]);
		if (!var[0])
			exit(0);
		if (check_valid_export(var[0]))
		{
			free_var(var, &s);
			continue ;
		}
		i = 0;
		if (look_for_match(var, args[s], p, &i))
			create_new_var(var, args[s], p, i);
		s++;
	}
	return (0);
}
