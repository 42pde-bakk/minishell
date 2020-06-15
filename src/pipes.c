/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer <pde-bakk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 16:22:16 by Peer          #+#    #+#                 */
/*   Updated: 2020/06/15 17:28:29 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		exec_without_fork(char **args, t_vars *p)
{
	int			i;
	char		*abspath;
	struct stat	statstr;

	i = 0;
	abspath = NULL;
	remove_quotes(args);
	get_abspath(&abspath, p, args);
	if (abspath && execve(abspath, args, p->env1) == -1)
		ft_dprintf(2, "bash: %s: %s\n", args[0], strerror(errno));
	else if (!abspath && args[0][0] != '.' && stat(args[0], &statstr) < 0)
		ft_dprintf(2, "bash: %s: command not found\n", args[0]);
	else if (!abspath && execve(args[0], args, p->env1) == -1)
		ft_dprintf(2, "bash: %s: %s\n", args[0], strerror(errno));
	p->is_child = 0;
	return_values(i, p);
}

static void	leftpipe(char **trimmedargs, int n, t_vars *p, int fd[2])
{
	(void)n;
	if (close(fd[0]) < 0)
		exit(1);
	if (dup2(fd[1], 1) < 0)
		exit(1);
	argcheck(trimmedargs, p, 0);
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
	int		i;

	i = 0;
	if (pipe(fd) == -1)
		exit(1);
	childpid = fork();
	if ((int)childpid == (pid_t)-1)
		exit(1);
	else if (childpid == (pid_t)0)
	{
		leftpipe(trimmed, n, p, fd);
		exit(0);
	}
	else
	{
		rightpipe(pipesplitcmds, n, p, fd);
		if (close(fd[1]) < 0)
			exit(1);
		waitpid(0, &i, 0);
	}
}
