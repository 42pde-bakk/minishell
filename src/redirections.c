/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 14:50:52 by peer          #+#    #+#                 */
/*   Updated: 2020/06/05 19:36:01 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_redirections(t_dup redirs)
{
	if (redirs.in)
	{
		redirs.input = NULL;
		if (dup2(redirs.stdinbak, 0) < 0)
		{
			perror("resetting stdin failed");
			exit(1);
		}
	}
	if (redirs.out)
	{
		redirs.output = NULL;
		if (dup2(redirs.stdoutbak, 1) < 0)
		{
			perror("resetting stdout failed");
			exit(1);
		}
	}
}

void	get_inout(t_dup *redirs, char **args)
{
	int i;
	int	check[2];

	i = 0;
	ft_bzero(redirs, sizeof(t_dup*));
	check[0] = 0;
	check[1] = 0;
	while (args[i])
	{
		if (ft_strncmp(args[i], "<", 2) == 0 && check[0] == 0)
		{
			redirs->in = 1;
			redirs->input = args[i + 1];
			free(args[i]);
			args[i] = ft_strdup("");
			check[0] = 1;
		}
		if (ft_strncmp(args[i], ">", 2) == 0 && check[1] == 0)
		{
			redirs->out = 1;
			redirs->output = args[i + 1];
			free(args[i]);
			args[i] = ft_strdup("");
			check[1] = 1;
		}
		else if (ft_strncmp(args[i], ">>", 3) == 0 && check[1] == 0)
		{
			redirs->out = 2;
			redirs->output = args[i + 1];
			free(args[i]);
			args[i] = ft_strdup("");
			check[1] = 2;
		}
		i++;
	}
}

t_dup	redirect(char **args)
{
	t_dup	redirs;
	int		fd[2];

	get_inout(&redirs, args);
	if (redirs.in)
	{
		fd[0] = open(redirs.input, O_RDONLY);
		redirs.stdinbak = dup(0);
		if (redirs.stdinbak < 0)
			exit(0);
		if (dup2(fd[0], 0) < 0)
			exit(0);
		close(fd[0]);
	}
	if (redirs.out)
	{
		if (redirs.out == 1)
			fd[1] = open(redirs.output, O_CREAT | O_TRUNC | O_RDWR, 0644);
		else if (redirs.out == 2)
			fd[1] = open(redirs.output, O_CREAT | O_APPEND | O_RDWR, 0644);
		redirs.stdoutbak = dup(1);
		if (redirs.stdoutbak < 0)
			exit(0);
		if (dup2(fd[1], 1) < 0)
			exit(0);
		close(fd[1]);
	}
	return (redirs);
}
