/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils3.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: wbarendr <wbarendr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 19:14:18 by wbarendr      #+#    #+#                 */
/*   Updated: 2020/06/04 15:58:41 by wbarendr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		block_ctrl_c(int sig)
{
	ft_putstr_fd("\nminishell> ", 1);
	sig = 0;
}

void		block_ctrl_slash(int sig)
{
	sig = 0;
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
	int i;

	i = 0;
	ft_putstr_fd("bash: ", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd(": command not found\n", 1);
}