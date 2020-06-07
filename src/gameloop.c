/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gameloop.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer <pde-bakk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 14:39:32 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/06/07 16:24:06 by Peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		trimcheck(char **args, int i)
{
	if (ft_strncmp(args[i], "", 1) != 0 &&
		(i == 0 || ft_strncmp(args[i - 1], "", 1) != 0))
		return (1);
	else
		return (0);
}

char	**trimargs(char **args)
{
	int		i;
	int		len;
	char	**out;

	i = 0;
	len = 0;
	while (args[i])
	{
		if (trimcheck(args, i) == 1)
			len++;
		i++;
	}
	i = 0;
	out = ft_calloc(len + 1, sizeof(char*));
	len = 0;
	while (args[i])
	{
		if (trimcheck(args, i) == 1)
		{
			out[len] = ft_strdup(args[i]);
			len++;
		}
		i++;
	}
	return (out);
}

int		do_pipes_and_redirs(char **pipesplitcmds, int n, t_vars *p)
{
	t_dup	redirs;
	char	**args;
	char	**trimmed;

	args = split_quotes2(pipesplitcmds[n]);
	ft_bzero(&redirs, sizeof(t_dup));
	redirect(args, &redirs);
	trimmed = trimargs(args);
	if (pipesplitcmds[n + 1])
		minipipe(pipesplitcmds, n, p);
	else if (args[0])
		argcheck(trimmed, p);
	reset_redirections(&redirs);
	free_args(trimmed);
	free_args(args);
	return (0);
}

int		gameloop(t_vars *p, char *line)
{
	int		i;
	int		n;
	char	**pipesplitcmds;
	char	**cmds;

	i = 0;
	cmds = NULL;
	if (line)
		cmds = ft_split_q(line, ';');
	while (cmds[i])
	{
		n = 0;
		pipesplitcmds = ft_split_q(cmds[i], '|');
		do_pipes_and_redirs(pipesplitcmds, n, p);
		i++;
		free_args(pipesplitcmds);
	}
	free_line_cmds(cmds, line, i);
	return (0);
}
