/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: Wester <Wester@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/27 13:56:51 by Wester        #+#    #+#                 */
/*   Updated: 2020/06/12 15:29:13 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_args(char **args)
{
	int i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_line_cmds(char **cmds, char *line, int i)
{
	while (cmds && i >= 0)
	{
		if (cmds[i])
			free(cmds[i]);
		i--;
	}
	free(cmds);
	free(line);
}

void	free_arr_top_down(char **arr, int *i)
{
	while (*i > 0)
	{
		free(arr[*i - 1]);
		(*i)--;
	}
	free(arr);
}

void	*ft_free_array(char **arr)
{
	unsigned int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

int		free_var_ret(char **var)
{
	free(var[0]);
	free(var);
	return (0);
}
