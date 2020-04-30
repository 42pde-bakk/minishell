/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: Wester <Wester@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 14:20:00 by Wester        #+#    #+#                 */
/*   Updated: 2020/04/30 14:43:59 by Wester        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_strcmp_equal(char *str1, char *str2)
{
	int i;

	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	if (str1[i] == '=')
		return (1);
	return (0);
}

void	remove_case(char **args)
{
	int i;

	i = 0;
	while ((*args)[i])
	{
		if ((*args)[i] >= 'A' && (*args)[i] <= 'Z')
			(*args)[i] += 32;
		i++;
	}
}

void	ft_putstr_fd_ret(char *str, int fd, t_vars *p)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			ft_putnbr_fd(p->ret, fd);
			i += 2;
		}
		else
		{ 
			write(fd, &str[i], 1);
			i++;
		}
	}
}