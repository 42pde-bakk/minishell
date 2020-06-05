/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer <pde-bakk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 16:22:16 by Peer          #+#    #+#                 */
/*   Updated: 2020/06/05 19:27:41 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>

static void	parent(char **pipesplitcmds, int n, t_vars *p, int fd[2])
{
	char	**args;
	int		stdoutbackup;

	stdoutbackup = dup(1);
	// dprintf(2, "entered parent ew\n");
	close(fd[0]);
	if (dup2(fd[1], 1) == -1)
		exit(0);
	args = split_quotes2(pipesplitcmds[n]);
	argcheck(args, p);
	close(fd[1]);
	if (dup2(stdoutbackup, 1) < 0)
		exit(0);
	free_args(args);
	waitpid(0, NULL, 0);
	// dprintf(2, "parent out\n");
}

/*
**                     	   p = fork();
**                         assume no errors
**                         you now have two
**                         programs running
**                         --------------------
**      if (p > 0) {                 |            if (p == 0) {
**         printf("parent\n");       |               printf("child\n");
**         ...                       |               ...
*/

int			minipipe(char **pipesplitcmds, int n, t_vars *p)
{
	int		fd[2];
	int		childpid;

	if (pipe(fd) == -1)
	{
		perror("pipe failed");
		return (-1);
	}
	childpid = fork();
	if (childpid == -1)
	{
		perror("fork failed");
		return (-1);
	}
	else if (childpid == 0)
	{
		// dprintf(2, "entered child ew\n");
		close(fd[1]);
		dup2(fd[0], 0);
		do_pipes_and_redirs(pipesplitcmds, n + 1, p);
		close(fd[0]);
		// dprintf(2, "child out\n");
		exit(0);
	}
	else
		parent(pipesplitcmds, n, p, fd);
	return (1);
}
