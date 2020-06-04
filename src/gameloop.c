/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gameloop.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 14:39:32 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/06/04 16:46:50 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_pipes_and_redirs(char **pipesplitcmds, int n, t_vars *p)
{
	t_dup	redir;
	char	**args;

	args = split_quotes2(pipesplitcmds[n]);
	redirect(args, &redir);
	if (pipesplitcmds[n + 1])
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

int	gameloop(t_vars *p, char *line)
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