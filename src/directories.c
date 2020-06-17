/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   directories.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 15:16:21 by peer          #+#    #+#                 */
/*   Updated: 2020/06/17 14:46:01 by wbarendr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		found_home(char *str)
{
	int		i;
	char	*new;

	i = 5;
	while (str[i])
		i++;
	new = malloc(i - 5 + 1);
	if (new == NULL)
		exit(1);
	i = 5;
	while (str[i])
	{
		new[i - 5] = str[i];
		i++;
	}
	new[i - 5] = 0;
	i = chdir(new);
	if (i < 0)
		ft_dprintf(2, "bash: cd: %s: %s\n", new, strerror(errno));
	free(new);
	return (i * -1);
}

int		cd_no_arg(t_vars *p)
{
	int		i;

	i = 0;
	while (p->env1[i])
	{
		if (find_match(p->env1[i], "HOME"))
		{
			if (p->env1[i][4] == '=')
				return (found_home(p->env1[i]));
		}
		i++;
	}
	ft_dprintf(2, "bash: cd: HOME not set\n");
	return (1);
}

int		cd(char **args, t_vars *p)
{
	char	*new;
	int		i;

	if (!args[1])
		return (cd_no_arg(p));
	if (args[1][0] == '~')
	{
		if (args[1][1] && args[1][2])
			new = ft_strjoin(p->home_path, args[1] + 2);
		else
			new = ft_strdup(p->home_path);
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

int		pwd(int fd)
{
	char	buf[10240];
	char	*ptr;

	ptr = getcwd(buf, 10240);
	if (ptr == NULL)
	{
		ft_dprintf(2, "bash: pwd: %s\n", strerror(errno));
		return (1);
	}
	ft_putstr_fd(ptr, fd);
	ft_putchar_fd('\n', fd);
	return (0);
}

int		env(char **args, t_vars *p, int fd)
{
	int	i;

	i = 0;
	(void)args;
	while (p->env1[i])
	{
		if (find_equal(p->env1[i]))
		{
			ft_putstr_fd(p->env1[i], fd);
			ft_putchar_fd('\n', fd);
		}
		i++;
	}
	return (0);
}
