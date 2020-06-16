/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils4.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer <pde-bakk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/16 16:33:42 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/06/17 01:38:13 by Peer          ########   odam.nl         */
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

void	return_values(t_vars *p)
{
	if (p->ret == 256)
		p->ret = 1;
	if (p->ret == 32512)
		p->ret = 127;
	if (p->ret == 2)
	{
		p->ret = 130;
		p->is_child = 1;
	}
	if (p->ret == 3)
	{
		p->ret = 131;
		p->is_child = 2;
	}
}

void	soul_goodman(t_vars *p, int *i)
{
	int soul;

	soul = 0;
	while (soul < p->pids)
	{
		waitpid(-1, &p->ret, 0);
		return_values(p);
		soul++;
	}
	(*i)++;
	free_int_array(p->pipes);
}
