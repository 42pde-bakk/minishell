/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gameloop.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer <pde-bakk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 14:39:32 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/06/17 17:03:06 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes(t_vars *p, int n)
{
	if (p->pipes)
	{
		if (p->pipes[n] && p->pipes[n][1] > 1)
		{
			close(p->pipes[n][1]);
			p->pipes[n][1] = -1;
		}
		if (n > 0 && p->pipes[n - 1] && p->pipes[n - 1][0] > 1)
		{
			close(p->pipes[n - 1][0]);
			p->pipes[n - 1][0] = -1;
		}
	}
}

int		pipe_do_stuff(char **pipesplitcmds, int n, t_vars *p)
{
	t_dup	redirs;
	char	**trimmed;
	char	**args;

	args = split_quotes2(pipesplitcmds[n]);
	if (args == NULL)
		exit(1);
	ft_bzero(&redirs, sizeof(redirs));
	if (p->pipes && p->pipes[n] && p->pipes[n][1] > 1)
	{
		redirs.out = p->pipes[n][1];
		redirs.ispipe[1] = 1;
	}
	if (p->pipes && n > 0 && p->pipes[n - 1] && p->pipes[n - 1][0] > 1)
	{
		redirs.in = p->pipes[n - 1][0];
		redirs.ispipe[0] = 1;
	}
	redirect(args, &redirs);
	trimmed = trimargs(args);
	fork_check(trimmed, p, &redirs);
	free_args(trimmed);
	free_args(args);
	close_pipes(p, n);
	return (0);
}

int		do_pipes_and_redirs(char **pipesplitcmds, int n, t_vars *p)
{
	pipe_do_stuff(pipesplitcmds, n, p);
	if (pipesplitcmds[n + 1])
		do_pipes_and_redirs(pipesplitcmds, n + 1, p);
	return (0);
}

void	setpipes(t_vars *p, char **pipesplitcmds)
{
	int	i;
	int	len;
	int **pipearray;

	i = 0;
	len = 0;
	p->pids = 0;
	while (pipesplitcmds[len])
		len++;
	if (len == 0)
		return ;
	pipearray = ft_calloc(len, sizeof(int *));
	if (pipearray == NULL)
		exit(1);
	while (i + 1 < len)
	{
		pipearray[i] = ft_calloc(3, sizeof(int));
		if (pipearray[i] == NULL)
			exit(1);
		if (pipe(pipearray[i]) == -1)
			exit(1);
		i++;
	}
	p->pipes = pipearray;
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
		soul_goodman(p, &i);
		free_args(pipesplitcmds);
	}
	free_line_cmds(cmds, line, i);
	return (0);
}
