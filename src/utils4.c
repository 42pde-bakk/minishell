/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils4.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 16:33:42 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/06/16 18:29:57 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(int fd)
{
	if (fd > 1)
		close(fd);
}

int		free_line(char *line)
{
	free(line);
	return (0);
}

void	free_int_array(int **arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	while (i >= 0)
	{
		free(arr[i]);
		arr[i] = NULL;
		i--;
	}
	free(arr);
	arr = NULL;
}

void	soul_goodman(t_vars *p, int *i)
{
	int soul;

	soul = 0;
	while (soul < p->pids)
	{
		waitpid(-1, &p->ret, 0);
		soul++;
	}
	(*i)++;
	free_int_array(p->pipes);
}
