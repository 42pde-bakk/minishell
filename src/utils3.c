/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils3.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer <pde-bakk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 19:14:18 by wbarendr      #+#    #+#                 */
/*   Updated: 2020/06/17 12:43:59 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		block_ctrl_c(int sig)
{
	g_ret = 1;
	ft_putstr_fd("\n\x1b[35;01mbash-3.3$\x1b[31;37m ", 1);
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
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void		get_environment2(char **env1, char *environ, int i)
{
	int k;

	k = 0;
	if (env1[i] == NULL)
	{
		free_args(env1);
		exit(1);
	}
	while (environ[k])
	{
		env1[i][k] = environ[k];
		k++;
	}
	env1[i][k] = 0;
}
