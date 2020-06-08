/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils3.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer <pde-bakk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 19:14:18 by wbarendr      #+#    #+#                 */
/*   Updated: 2020/06/08 16:56:34 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		block_ctrl_c(int sig)
{
	ft_putstr_fd("\nminishell> ", 1);
	(void)sig;
}

void		block_ctrl_slash(int sig)
{
	(void)sig;
}

int			run_back_slash(char *str, int *index)
{
	int i;
	int ret;

	ret = 0;
	i = *index - 1;
	while (i >= 0)
	{
		if (str[i] != '\\')
			break ;
		ret++;
		i--;
	}
	return (ret % 2);
}

void		not_found(char *str)
{
	ft_putstr_fd("bash: ", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd(": command not found\n", 1);
}