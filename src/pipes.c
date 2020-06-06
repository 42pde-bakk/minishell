/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer <pde-bakk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 16:22:16 by Peer          #+#    #+#                 */
/*   Updated: 2020/06/06 20:46:44 by Peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>

static void	leftpipe(char **pipesplitcmds, int n, t_vars *p, int fd[2])
{
	char	**args;

	close(fd[0]);
	if (dup2(fd[1], 1) < 0)
		exit(1);
	args = split_quotes2(pipesplitcmds[n]);
	argcheck(args, p);
	close(fd[1]);
	free_args(args);
}

static void	rightpipe(char **pipesplitcmds, int n, t_vars *p, int fd[2])
{
	int	stdinbackup;

	stdinbackup = dup(0);
	close(fd[1]);
	if (dup2(fd[0], 0) < 0)
		exit(1);
	do_pipes_and_redirs(pipesplitcmds, n + 1, p);
	close(fd[0]);
	if (dup2(stdinbackup, 0) < 0)
		exit(1);
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

void		minipipe(char **pipesplitcmds, int n, t_vars *p)
{
	int		fd[2];
	int		childpid;

	if (pipe(fd) == -1)
	{
		perror("pipe failed");
		exit(1);
	}
	childpid = fork();
	if (childpid == -1)
	{
		perror("fork failed");
		exit(1);
	}
	else if (childpid == 0)
	{
		leftpipe(pipesplitcmds, n, p, fd);
		exit(0);
	}
	else
	{
		rightpipe(pipesplitcmds, n, p, fd);
		waitpid(0, NULL, 0);
	}
}
