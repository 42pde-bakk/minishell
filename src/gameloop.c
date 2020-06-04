/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gameloop.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 14:39:32 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/06/04 16:23:56 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_pipes_and_redirs(char **pipesplitcmds, int n, t_vars *p)
{
	t_dup	redir;
	char	**args;

	args = split_quotes2(pipesplitcmds[n]);
	redirect(args, &redir);
	if (pipesplitcmds[n + 1]) //theres another command behind a pipe
	{
		minipipe(pipesplitcmds, n, p);
	}
	else if (args[0])
	{
		argcheck(args, p);
	}
	reset_redirect(&redir);
	free_args(args);
	return (0);
}

int	gameloop(char **cmds, t_vars *p, char *line)
{
	int		i;
	int		n;
	char	**pipesplitcmds;

	i = 0;
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