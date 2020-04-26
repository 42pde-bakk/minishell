/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   directories.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 15:16:21 by peer          #+#    #+#                 */
/*   Updated: 2020/04/26 16:46:22 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		cd(char **args)
{
	char	*new;

	if (args[1][0] == '~')
	{
		new = args[1];
		(new)++;
		new = ft_strjoin("/home/peer", new);
		chdir(new);
	}
	else
		chdir(args[1]);
	free(args[1]);
	return (0);
}

int		pwd(void)
{
	char	buf[10240];
	char	*ptr;

	ptr = getcwd(buf, 10240);
	ft_putstr_fd(ptr, 1);
	ft_putchar_fd('\n', 1);
	return (0);
}
