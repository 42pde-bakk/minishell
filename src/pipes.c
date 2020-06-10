/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer <pde-bakk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 16:22:16 by Peer          #+#    #+#                 */
/*   Updated: 2020/06/10 19:13:22 by Peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>

static void	leftpipe(char **trimmedargs, int n, t_vars *p, int fd[2])
{
	(void)n;
	if (close(fd[0]) < 0)
		exit(1);
	if (dup2(fd[1], 1) < 0)
		exit(1);
	argcheck(trimmedargs, p);
	dprintf(2, "left side is done with args\n");
	if (close(fd[1]) < 0)
		exit(1);
}

static void	rightpipe(char **pipesplitcmds, int n, t_vars *p, int fd[2])
{
	int	stdinbackup;

	stdinbackup = dup(0);
	if (close(fd[1]) < 0)
		exit(1);
	if (dup2(fd[0], 0) < 0)
		exit(1);
	do_pipes_and_redirs(pipesplitcmds, n + 1, p);
	if (close(fd[0]) < 0)
		exit(1);
	if (dup2(stdinbackup, 0) < 0)
		exit(1);
}

/*
**                     	   p = fork();
**                         assume no errors
**                         you now have two
**                         programs running
**                         --------------------
**      if (p == 0) {               |            if (p > 0) {
**         printf("leftpipe\n");    |               printf("rightpipe\n");
**         ...                      |               ...
*/

void		minipipe(char **pipesplitcmds, int n, t_vars *p, char **trimmed)
{
	int		fd[2];
	pid_t	childpid;

	if (pipe(fd) == -1)
	{
		perror("pipe failed");
		exit(1);
	}
	childpid = fork();
	if ((int)childpid == (pid_t)-1)
	{
		perror("fork failed");
		exit(1);
	}
	else if (childpid == (pid_t)0)
	{
		leftpipe(trimmed, n, p, fd);
		exit(0);
	}
	else
	{
		rightpipe(pipesplitcmds, n, p, fd);
		dprintf(2, "rightpipe is waiting\n");
		if (close(fd[1]) < 0)
			exit(1);
		waitpid(0, NULL, 0);
		dprintf(2, "rightpipe is done waiting\n");
	}
}
