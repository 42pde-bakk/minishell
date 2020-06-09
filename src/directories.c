/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   directories.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 15:16:21 by peer          #+#    #+#                 */
/*   Updated: 2020/06/09 17:32:42 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		cd(char **args)
{
	char	*new;
	int		i;

	if (!args[1])
		return (0);
	if (args[1][0] == '~')
	{
		new = args[1];
		(new)++;
		new = ft_strjoin("/home/peer", new);
		i = chdir(new);
	}
	else
	{
		i = chdir(args[1]);
		if (i < 0)
			ft_dprintf(2, "bash: cd: %s: %s\n", args[1], strerror(errno));
	}
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

int		env(char **args, t_vars *p)
{
	int	i;

	i = 0;
	(void)args;
	while (p->env1[i])
	{
		if (find_equal(p->env1[i]))
		{
			ft_putstr_fd(p->env1[i], 1);
			ft_putchar_fd('\n', 1);
		}
		i++;
	}
	return (0);
}
