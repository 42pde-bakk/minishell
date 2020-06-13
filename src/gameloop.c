/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gameloop.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer <pde-bakk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 14:39:32 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/06/13 23:40:14 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		do_pipes_and_redirs(char **pipesplitcmds, int n, t_vars *p)
{
	t_dup	redirs;
	char	**args;
	char	**trimmed;

	args = split_quotes2(pipesplitcmds[n]);
	if (args == NULL)
		exit(1);
	ft_bzero(&redirs, sizeof(t_dup));
	redirect(args, &redirs);
	trimmed = trimargs(args);
	if (pipesplitcmds[n + 1])
		minipipe(pipesplitcmds, n, p, trimmed);
	else if (trimmed[0] && trimmed[0][0] != '<' && trimmed[0][0] != '>')
		argcheck(trimmed, p);
	reset_redirections(&redirs);
	free_args(trimmed);
	free_args(args);
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
		do_pipes_and_redirs(pipesplitcmds, n, p);
		i++;
		free_args(pipesplitcmds);
	}
	free_line_cmds(cmds, line, i);
	return (0);
}
