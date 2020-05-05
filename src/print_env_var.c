/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_env_var.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: Wester <Wester@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/30 13:41:35 by Wester        #+#    #+#                 */
/*   Updated: 2020/05/05 15:21:45 by Wester        ########   odam.nl         */
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

/* int		check_end_path(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return 0;
	if (c == 95)
		return 0;
	return (1);
} */

/* int		print_env_var(char *args, t_vars *p, int fd, int i)
{
	int k;
	int l;

	l = 0;
	k = 0;
	while (p->env1[k])
	{
		while (p->env1[k][l] == args[i + 1 + l] && p->env1[k][l])
			l++;
		if (p->env1[k][l] == '=' && check_end_path(args[i + 1 + l]))
		{
			l++;
			while (p->env1[k][l])
			{
				write(fd, &p->env1[k][l], 1);
				l++;
			}
			return (0);
		}
		l = 0;
		k++;
	}
	return (0);
} */