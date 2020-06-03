/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer <pde-bakk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 16:22:16 by Peer          #+#    #+#                 */
/*   Updated: 2020/06/03 21:16:50 by Peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>

int	getpipes(char **args)
{
	int	i;
	int	ret;

	i = 0;
	ret = -1;
	while (args[i])
	{
		if (strncmp(args[i], "|", 2) == 0)
			ret = i;
		i++;
	}
	return (ret);
}

char	**getchildargs(char **args)
{
	int	i;
	int	childstart;
	char	**childargs;

	i = 0;
	childstart = 0;
	while (args[i])
	{
		if (strncmp(args[i], "|", 2) == 0)
			childstart = i + 1;
		i++;
	}
	childargs = malloc(sizeof(char*) * i - childstart + 2);
	i = 0;
	while (args[childstart + i])
	{
		childargs[i] = malloc(sizeof(char) * ft_strlen(args[i + childstart] + 1));
		childargs[i] = ft_strdup(args[i + childstart]);
		dprintf(2, "childargs[%i]: %s\n", i, childargs[i]);
		i++;
	}
	return (childargs);
}

void	freechildargs(char **childargs)
{
	int i;

	i = 0;
	while (childargs[i])
	{
		free(childargs[i]);
		i++;
	}
	free(childargs);
}

/*
**                     	   p = fork();
**                         assume no errors
**                         you now have two
**                         programs running
**                         --------------------
**      if (p == 0) {               |            if (p > 0) {
**        printf("child\n");        |              printf("parent\n");
**        ...                       |              ...
*/

int	minipipe(char **args, t_vars *p)
{
	int		fd[2];
	int		childpid;
	char	**childargs;

	(void)p;
	(void)args;
	(void)childargs;
	if (pipe(fd) == -1)
	{
		perror("pipe failed");
		return (-1);
	}
	childpid = fork();
	printf("pipe: [%d, %d] & childpid=%d\n", fd[0], fd[1], childpid);
	if (childpid == -1)
	{
		perror("fork failed");
		return (-1);
	}
	else if (childpid == 0) //Child process
	{
        // child side
        // close write side. don't need it.
		char buf[20];
		read(fd[0], buf, 19);
		char buf2[20];
		read(fd[1], buf2, 19);
		fprintf(stderr, "fd[0]: %s\nfd[1]: %s\n", buf, buf2);
        close(fd[1]);

		childargs = getchildargs(args);
		argcheck(childargs, p);
		close(fd[0]);
		freechildargs(childargs);
		fprintf(stdout, "Child: shutting down.\n");	
	}
	else
	{
		// close read size. don't need it.
        close(fd[0]);
		int backup = dup(1);
		dup2(fd[1], 1); //now all my args will write to fd[1] instead ouf stdout

        sleep(5); // simulate process wait
		argcheck(args, p);
		dup2(backup, 1); //resetting stdout stream
        close(fd[1]);
	}
	return (1);
}