/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_env_var.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: Wester <Wester@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/30 13:41:35 by Wester        #+#    #+#                 */
/*   Updated: 2020/04/30 15:35:33 by Wester        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	uppercase_str(char **str)
// {
// 	int i;

// 	i = 1;
// 	while ((*str)[i])
// 	{
// 		(*str)[i] -= 32;
// 		i++;
// 	}
// }

int		print_env_var(char *args, t_vars *p, int fd)
{
	int k;
	int i;

	k = 0;
	i = 0;
	while (p->env1[k])
	{
		while (p->env1[k][i] == args[i + 1] && p->env1[k][i])
			i++;
		if (p->env1[k][i] == '=' && args[i + 1] == 0)
		{
			i++;
			while (p->env1[k][i])
			{
				write(fd, &p->env1[k][i], 1);
				i++;
			}
			return (0);
		}
		i = 0;
		k++;
	}
	return (0);
}