/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: Wester <Wester@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/27 13:56:51 by Wester        #+#    #+#                 */
/*   Updated: 2020/05/27 13:59:56 by Wester        ########   odam.nl         */
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
	while (i >= 0)
	{
		if (cmds[i])
			free(cmds[i]);
		i--;
	}
	free(cmds);
	free(line);
}
