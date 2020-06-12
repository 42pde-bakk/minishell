/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   directories.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 15:16:21 by peer          #+#    #+#                 */
/*   Updated: 2020/06/12 16:45:09 by wbarendr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		cd(char **args, t_vars *p)
{
	char	*new;
	int		i;

	if (!args[1])
		return (0);
	if (args[1][0] == '~')
	{
		if (args[1][1] && args[1][2])
			new = ft_strjoin(p->home_path, args[1] + 2);
		else
			new = p->home_path;
		if (new == NULL)
			exit(1);
		i = chdir(new);
		if (i < 0)
			ft_dprintf(2, "bash: cd: %s: %s\n", args[1], strerror(errno));
		free(new);
	}
	else if (1)
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
	{
		ft_dprintf(2, "bash: pwd: %s\n", strerror(errno));
		return (1);
	}
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
