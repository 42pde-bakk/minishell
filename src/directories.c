/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   directories.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 15:16:21 by peer          #+#    #+#                 */
/*   Updated: 2020/04/25 17:41:45 by peer          ########   odam.nl         */
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

int		pwd(int fd)
{
	char	buf[10240];
	char	*ptr;

	ptr = getcwd(buf, 10240);
	ft_putstr_fd(ptr, fd);
	ft_putchar_fd('\n', fd);
	return (0);
}
