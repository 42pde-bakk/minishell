/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer <pde-bakk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 14:50:52 by peer          #+#    #+#                 */
/*   Updated: 2020/06/15 19:01:18 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_redirections(t_dup *redirs)
{
	if (redirs->in)
	{
		redirs->in = 0;
		redirs->input = NULL;
		if (dup2(redirs->stdinbak, 0) < 0)
		{
			strerror(errno);
			exit(1);
		}
	}
	if (redirs->out)
	{
		redirs->out = 0;
		redirs->output = NULL;
		if (dup2(redirs->stdoutbak, 1) < 0)
		{
			strerror(errno);
			exit(1);
		}
	}
}

void	get_backup(t_dup *redirs)
{
	redirs->stdinbak = dup(0);
	if (redirs->stdinbak < 0)
		exit(1);
	redirs->stdoutbak = dup(1);
	if (redirs->stdoutbak < 0)
		exit(1);
}

void	redirect_output(char **args, t_dup *redirs, int *i)
{
	redirs->output = args[*i + 1];
	if (ft_strncmp(args[*i], ">", 2) == 0)
		redirs->out = open(redirs->output, O_CREAT | O_TRUNC | O_RDWR, 0644);
	else
		redirs->out = open(redirs->output, O_CREAT | O_APPEND | O_RDWR, 0644);
	// if (dup2(redirs->out, 1) < 0)
	// 	exit(0);
	// close(redirs->out);
}

void	redirect(char **args, t_dup *redirs)
{
	int		i;

	i = 0;
	// get_backup(redirs);
	while (args[i])
	{
		if (ft_strncmp(args[i], "<", 2) == 0 && args[i + 1])
		{
			redirs->input = args[i + 1];
			redirs->in = open(redirs->input, O_RDONLY);
			// if (dup2(redirs->in, 0) < 0)
			// 	exit(0);
			// close(redirs->in);
		}
		if ((ft_strncmp(args[i], ">", 2) == 0 ||
			ft_strncmp(args[i], ">>", 3) == 0) && args[i + 1])
			redirect_output(args, redirs, &i);
		i++;
	}
}
