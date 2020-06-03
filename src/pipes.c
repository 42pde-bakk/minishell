/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer <pde-bakk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 16:22:16 by Peer          #+#    #+#                 */
/*   Updated: 2020/06/03 18:32:11 by Peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

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
	childargs = malloc(sizeof(char**) * i - childstart + 2);
	i = 0;
	while (args[childstart])
	{
		childargs[i] = ft_strdup(args[i + childstart]);
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
		dup2(fd[0], 0);
		childargs = getchildargs(args);
		argcheck(childargs, p);
		freechildargs(childargs);
    //   read(fd[0], readmessage, sizeof(readmessage));
    //   printf("Child Process - Reading from pipe – Message 1 is %s\n", readmessage);
    //   read(fd[0], readmessage, sizeof(readmessage));
    //   printf("Child Process - Reading from pipe – Message 2 is %s\n", readmessage);
   } else { //Parent process
		int	stdoutbak = dup(1);
		dup2(fd[1], 1);
		wait(NULL);
		argcheck(args, p);
		dup2(stdoutbak, 1);
    //   printf("Parent Process - Writing to pipe - Message 1 is %s\n", writemessages[0]);
    //   write(fd[1], writemessages[0], sizeof(writemessages[0]));
    //   printf("Parent Process - Writing to pipe - Message 2 is %s\n", writemessages[1]);
    //   write(fd[1], writemessages[1], sizeof(writemessages[1]));
	}
	return (1);
}