/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer <pde-bakk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 14:50:52 by peer          #+#    #+#                 */
/*   Updated: 2020/06/17 13:02:52 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_output(char **args, t_dup *redirs, int *i)
{
	redirs->output = args[*i + 1];
	if (redirs->out > 1)
		close(redirs->out);
	if (ft_strncmp(args[*i], ">", 2) == 0)
		redirs->out = open(redirs->output, O_CREAT | O_TRUNC | O_RDWR, 0644);
	else
		redirs->out = open(redirs->output, O_CREAT | O_APPEND | O_RDWR, 0644);
}

void	redirect(char **args, t_dup *redirs)
{
	int		i;

	i = 0;
	while (args[i])
	{
		if (ft_strncmp(args[i], "<", 2) == 0 && args[i + 1])
		{
			redirs->input = args[i + 1];
			if (redirs->in > 0)
				close(redirs->in);
			redirs->in = open(redirs->input, O_RDONLY);
		}
		if ((ft_strncmp(args[i], ">", 2) == 0 ||
			ft_strncmp(args[i], ">>", 3) == 0) && args[i + 1])
			redirect_output(args, redirs, &i);
		i++;
	}
}
