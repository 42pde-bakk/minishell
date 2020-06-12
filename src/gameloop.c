/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gameloop.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer <pde-bakk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 14:39:32 by pde-bakk      #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2020/06/12 16:45:23 by wbarendr      ########   odam.nl         */
=======
/*   Updated: 2020/06/12 17:36:25 by pde-bakk      ########   odam.nl         */
>>>>>>> 2348e2b2a4ac84f76ce6d66fc6dfc354e0483bc8
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
	{
		minipipe(pipesplitcmds, n, p, trimmed);
	}
	else if (trimmed[0] && trimmed[0][0] != '<' && trimmed[0][0] != '>')
	{
		argcheck(trimmed, p);
	}
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
	if (syntax_check(line))
	{
		free(line);
		return (0);
	}
	line = improve_line(line);
	if (line)
		cmds = ft_split_q(line, ';');
<<<<<<< HEAD
	if (cmds == NULL)
		exit(1);
	while (cmds[i])
=======
	while (cmds && cmds[i])
>>>>>>> 2348e2b2a4ac84f76ce6d66fc6dfc354e0483bc8
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
