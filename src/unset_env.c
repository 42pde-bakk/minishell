/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset_env.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Wester <Wester@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 15:43:45 by Wester        #+#    #+#                 */
/*   Updated: 2020/04/16 16:57:40 by Wester        ########   odam.nl         */
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
				exit(0);
			while (p->env1[i][k])
			{
				arr[i2][k] = p->env1[i][k];
				k++;
			}
			k = 0;
			i2++;
		}
		i++;
	}
	arr[i2] = 0;
	free_old_arr(p);
	p->env1 = arr;
}

void            unset_new(char **args, t_vars *p)
{
	char    **var;
	int     i;
	int		found;

	i = 0;
	found = -1;
	if (!args[1])
		return ;
	var = ft_split(args[1], '=');
	if (!var)
		exit(0);
	while (p->env1[i])
	{
		if (ft_strcmp_equal(p->env1[i], var[0]))
			found = i;
		i++;
	}
	if (found >= 0)
		make_smaller_array(found, i, p);
	//printf("%s\n", var[0]);
	//printf("found: %d\n", found);
}