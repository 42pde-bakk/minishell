/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset_env.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Wester <Wester@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 15:43:45 by Wester        #+#    #+#                 */
/*   Updated: 2020/05/20 15:36:52 by Wester        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void            free_old_arr(t_vars *p)
{
	int i;

	i = 0;
	while (p->env1[i])
	{
		free(p->env1[i]);
		i++;
	}
	free(p->env1);
}

void            make_smaller_array(int found, int total_size, t_vars *p)
{
	int		i;
	int		i2;
	char	**arr;
	int		k;

	i = 0;
	i2 = 0;
	k = 0;
	arr = malloc(sizeof(char *) * total_size);
	if (!arr)
		exit(0);
	while (p->env1[i])
	{
		if (i != found)
		{
			arr[i2] = malloc(ft_strlen(p->env1[i]) + 1);
			if (!arr[i2])
				exit(0); // malloc fail
			printf("in: %s$\n", p->env1[i]);
			while (p->env1[i][k])
			{
				arr[i2][k] = p->env1[i][k];
				k++;
			}
			arr[i2][k] = 0;
			printf("ot: %s$\n", arr[i2]);
			k = 0;
			i2++;
		}
		i++;
	}
	arr[i2] = 0;
	free_old_arr(p);
	i = 0;
	while (arr[i])
	{
		p->env1[i] = arr[i];
		i++;
	}
	p->env1[i] = 0;
	p->env1 = arr;
}

int            unset_new(char **args, t_vars *p)
{
	int     i;
	int		found;
	int 	k;

	k = 1;
	if (!args[1])
		return (0);
	while (args[k])
	{
		i = 0;
		found = -1;
		check_valid_export(args[k]);
		while (p->env1[i])
		{
			if (ft_strcmp_equal(p->env1[i], args[k]))
				found = i;
			i++;
		}
		if (found >= 0)
			make_smaller_array(found, i, p);
		k++;
	}
	return (0);
}