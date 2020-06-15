/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gameloop.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer <pde-bakk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 14:39:32 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/06/15 23:58:11 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	closepipes(t_pipes *pipes)
{
	// if (pipes->currpipe[0] > 1)
	// 	if (close(pipes->currpipe[0] == -1))
	// 		exit(1);
	if (pipes->prevpipe[0] > 1)
		if (close(pipes->prevpipe[0] == -1))
			exit(1);
	pipes->prevpipe[0] = 0;
	// if (pipes->prevpipe[1] > 1)
	// 	if (close(pipes->prevpipe[1] == -1))
	// 		exit(1);
	// pipes->prevpipe[1] = 0;
	if (pipes->currpipe[1] > 1)
		if (close(pipes->currpipe[1] == -1))
			exit(1);
	pipes->currpipe[1] = 0;
}

int		lefthandpipe(char **pipesplitcmds, int n, t_vars *p, t_pipes pipes)
{
	t_dup	redirs;
	char	**trimmed;
	char	**args;

	args = split_quotes2(pipesplitcmds[n]);
	ft_dprintf(2, "lh: args[0] = %s, prevpipe = [%d, %d], currpipe = [%d, %d]\n", args[0], pipes.prevpipe[0], pipes.prevpipe[1], pipes.currpipe[0], pipes.currpipe[1]);
	if (args == NULL)
		exit(1);
	ft_bzero(&redirs, sizeof(redirs));
	if (pipes.prevpipe[0] > 1)
	{
		redirs.in = pipes.prevpipe[0];
		ft_dprintf(2, "%s gon read from fd: %d\n", args[0], redirs.in);
	}
	if (pipes.currpipe[1] > 1)
	{
		redirs.out = pipes.currpipe[1];
		ft_dprintf(2, "%s gon write to fd: %d\n", args[0], redirs.out);
	}
	redirect(args, &redirs);
	trimmed = trimargs(args);
	argcheck(trimmed, p, &redirs);
	closepipes(&pipes);
	ft_dprintf(2, "%s closed pipes: prev = [%d, %d], curr = [%d, %d]\n", args[0], pipes.prevpipe[0], pipes.prevpipe[1], pipes.currpipe[0], pipes.currpipe[1]);
	free_args(trimmed);
	free_args(args);
	return (0);
}

t_pipes	init_pipes(t_pipes pipes)
{
	pipes.prevpipe[0] = pipes.currpipe[0];
	pipes.prevpipe[1] = pipes.currpipe[1];
	ft_bzero(&pipes.currpipe, sizeof(pipes.currpipe));
	ft_bzero(&pipes.inuse, sizeof(pipes.inuse));
	return (pipes);
}

int		do_pipes_and_redirs(char **pipesplitcmds, int n, t_vars *p,
t_pipes pipes)
{
	pipes = init_pipes(pipes);
	if (pipesplitcmds[n + 1] == NULL)
		return (lefthandpipe(pipesplitcmds, n, p, pipes));
	if (pipe(pipes.currpipe) == -1)
		exit(1);
	lefthandpipe(pipesplitcmds, n, p, pipes);
	do_pipes_and_redirs(pipesplitcmds, n + 1, p, pipes);
	ft_dprintf(2, "after all calls\n");
	// close(pipes.currpipe[0]);
	// close(pipes.currpipe[1]);
	return (0);
}

int		free_line(char *line)
{
	free(line);
	return (0);
}

int		gameloop(t_vars *p, char *line)
{
	int		i;
	int		n;
	char	**pipesplitcmds;
	char	**cmds;
	t_pipes	pipes;

	i = 0;
	cmds = NULL;
	if (syntax_check(line))
		return (free_line(line));
	line = improve_line(line);
	if (line)
		cmds = ft_split_q(line, ';');
	while (cmds && cmds[i])
	{
		n = 0;
		pipesplitcmds = ft_split_q(cmds[i], '|');
		if (pipesplitcmds == NULL)
			exit(1);
		ft_bzero(&pipes, sizeof(t_pipes));
		do_pipes_and_redirs(pipesplitcmds, n, p, pipes);
		i++;
		free_args(pipesplitcmds);
	}
	free_line_cmds(cmds, line, i);
	return (0);
}
