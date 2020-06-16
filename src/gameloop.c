/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gameloop.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer <pde-bakk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 14:39:32 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/06/16 15:05:30 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		pipe_do_stuff(char **pipesplitcmds, int n, t_vars *p)
{
	t_dup	redirs;
	char	**trimmed;
	char	**args;

	args = split_quotes2(pipesplitcmds[n]);
	if (args == NULL)
		exit(1);
	ft_bzero(&redirs, sizeof(redirs));
	if (p->pipes[n][1] > 1)
		redirs.out = p->pipes[n][1];
	if (n > 0 && p->pipes[n - 1][0] > 1)
		redirs.in = p->pipes[n - 1][0];
	redirect(args, &redirs);
	trimmed = trimargs(args);
	argcheck(trimmed, p, &redirs);
	free_args(trimmed);
	free_args(args);
	if (p->pipes[n][1] > 1)
		close(p->pipes[n][1]);
	if (n > 0 && p->pipes[n - 1][0] > 1)
		close(p->pipes[n - 1][0]);
	// close(redirs.in);
	// close(redirs.out);
	// close(p->pipes[n][1]);
	// if (n > 0)
	// 	close(p->pipes[n - 1][0]);
	return (0);
}

int		do_pipes_and_redirs(char **pipesplitcmds, int n, t_vars *p)
{
	pipe_do_stuff(pipesplitcmds, n, p);
	if (pipesplitcmds[n + 1])
		do_pipes_and_redirs(pipesplitcmds, n + 1, p);
	return (0);
}

int		free_line(char *line)
{
	free(line);
	return (0);
}

void	setpipes(t_vars *p, char **pipesplitcmds)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	ft_bzero(&p->pipes, sizeof(p->pipes));
	while (pipesplitcmds[n + 1])
	{
		// p->pipes[n] = ft_calloc(1, sizeof(int[2]));
		if (pipe(p->pipes[n]) == -1)
			exit(1);
		// ft_dprintf(2, "created a pipe for p->pipes[%d]: [%d, %d]\n", n, p->pipes[n][0], p->pipes[n][1]);
		n++;
	}
	// ft_dprintf(2, "extra pipe for n=%d: [%d, %d]\n", n, p->pipes[n][0], p->pipes[n][1]);
}

int		gameloop(t_vars *p, char *line)
{
	int		i;
	int		n;
	char	**pipesplitcmds;
	char	**cmds;

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
		setpipes(p, pipesplitcmds);
		do_pipes_and_redirs(pipesplitcmds, n, p);
		i++;
		free_args(pipesplitcmds);
	}
	free_line_cmds(cmds, line, i);
	return (0);
}
