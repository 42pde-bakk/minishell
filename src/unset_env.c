/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset_env.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Wester <Wester@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 15:43:45 by Wester        #+#    #+#                 */
/*   Updated: 2020/06/12 17:18:17 by wbarendr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_old_arr(t_vars *p, char **arr, int i2)
{
	int i;

	i = 0;
	arr[i2] = 0;
	while (p->env1[i])
	{
		free(p->env1[i]);
		i++;
	}
	free(p->env1);
	i = 0;
	p->env1 = arr;
}

void		make_smaller_array(int found, t_vars *p, char **arr, int k)
{
	int		i;
	int		i2;

	i = 0;
	i2 = 0;
	while (p->env1[i])
	{
		if (i != found)
		{
			arr[i2] = malloc(ft_strlen(p->env1[i]) + 1);
			if (!arr[i2])
				exit(1);
			while (p->env1[i][k])
			{
				arr[i2][k] = p->env1[i][k];
				k++;
			}
			arr[i2][k] = 0;
			k = 0;
			i2++;
		}
		i++;
	}
	free_old_arr(p, arr, i2);
}

void		unset_new2(int found, t_vars *p, char **arr)
{
	if (found >= 0)
		make_smaller_array(found, p, arr, 0);
	else
		free(arr);
}

int			unset_new(char **args, t_vars *p)
{
	int		i;
	int		found;
	int		k;
	char	**arr;

	k = 1;
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
		arr = malloc(sizeof(char *) * i);
		if (!arr)
			exit(1);
		unset_new2(found, p, arr);
		k++;
	}
	return (0);
}
