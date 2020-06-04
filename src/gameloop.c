/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gameloop.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 14:39:32 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/06/04 15:12:41 by pde-bakk      ########   odam.nl         */
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
		dprintf(2, "Entering pipeline\n");
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
		while (pipesplitcmds[n])
		{
			do_pipes_and_redirs(pipesplitcmds, n, p);
			n++;
		}
		i++;
	}
	free_line_cmds(cmds, line, i);
	return (0);
}