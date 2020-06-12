/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   trimming.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/12 17:36:03 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/06/12 17:37:07 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Checks if current arg isnt </>/>> and
** if either i == 0 or the previous argument isnt </>/>>
*/

int		trimcheck(char **args, int i)
{
	if ((ft_strncmp(args[i], "<", 2) != 0 && ft_strncmp(args[i], ">", 2) &&
	ft_strncmp(args[i], ">>", 3) != 0) && (i == 0 ||
	(ft_strncmp(args[i - 1], "<", 2) != 0 && ft_strncmp(args[i - 1], ">", 2)
	&& ft_strncmp(args[i - 1], ">>", 3) != 0)))
		return (1);
	else
		return (0);
}

char	**trimloop(char **args, char **out)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (args[i])
	{
		if (trimcheck(args, i) == 1)
		{
			out[len] = ft_strdup(args[i]);
			if (out[len] == NULL)
			{
				free_args(out);
				return ((char**)NULL);
			}
			len++;
		}
		i++;
	}
	return (out);
}

char	**trimargs(char **args)
{
	int		i;
	int		len;
	char	**out;

	i = 0;
	len = 0;
	while (args[i])
	{
		if (trimcheck(args, i) == 1)
			len++;
		i++;
	}
	i = 0;
	out = ft_calloc(len + 1, sizeof(char*));
	if (out == NULL)
		return (out);
	return (trimloop(args, out));
}
