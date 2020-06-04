/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer <pde-bakk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 16:22:16 by Peer          #+#    #+#                 */
/*   Updated: 2020/06/04 15:14:59 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>

/*
**                     	   p = fork();
**                         assume no errors
**                         you now have two
**                         programs running
**                         --------------------
**      if (p > 0) {                 |            if (p == 0) {
**         printf("parent\n");       |               printf("child\n"); (parent feeds the child)
**         ...                       |               ...
*/

int	minipipe(char **pipesplitcmds, int n, t_vars *p)
{
	int		fd[2];
	int		childpid;
	char	**args; 

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
	else if (childpid == 0) //Child process
	{
        // child side
        // close writing end of the pipe. don't need it.
        close(fd[1]);

		dup2(fd[0], 0);
		do_pipes_and_redirs(pipesplitcmds, n + 1, p);
		close(fd[0]);
		fprintf(stdout, "Child: shutting down.\n");	
	}
	else //Parent process
	{
		// close reading end of the pipe. don't need it.
		int stdoutbackup = dup(1);
		close(fd[0]);
		dup2(fd[1], 1); //now all my args will write to fd[1] instead ouf stdout

		args = split_quotes2(pipesplitcmds[n]);
		argcheck(args, p);
		dprintf(2, "argcheck for parent done\n");
		dprintf(2, "parent done waiting\n");
		close(fd[1]);
		if (dup2(stdoutbackup, 1) < 0)
		{
			dprintf(2, "resetting stdout failed\n");
			return (-1);
		}
		dprintf(2, "Parent: shutting down.\n");
		printf("stdout test\n");
		waitpid(0, NULL, 0); // simulate process wait
	}
	return (1);
}