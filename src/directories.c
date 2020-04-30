/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   directories.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 15:16:21 by peer          #+#    #+#                 */
/*   Updated: 2020/04/30 16:19:45 by Wester        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		cd(char **args)
{
	char	*new;
	int i;

	if (args[1][0] == '~')
	{
		new = args[1];
		(new)++;
		new = ft_strjoin("/home/peer", new);
		i = chdir(new);
	}
	else
		i = chdir(args[1]);
	return (i * -1);
}

int		pwd(void)
{
	char	buf[10240];
	char	*ptr;

	ptr = getcwd(buf, 10240);
	if (ptr == NULL)
		return (1);
	ft_putstr_fd(ptr, 1);
	ft_putchar_fd('\n', 1);
	return (0);
}
