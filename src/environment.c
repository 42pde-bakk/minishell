/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environment.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 15:21:02 by peer          #+#    #+#                 */
/*   Updated: 2020/04/14 18:03:221 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		print_export(char **args, t_vars *p, int fd)
{
	int	i;
	char **arr;

	i = 0;
	arr = bubble_sort(p->env1);
	while (arr[i])
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(arr[i], fd);
		ft_putchar_fd('\n', fd);
		i++;
	}
	return (0);
}

int		export(char **args, t_vars *p, int fd)
{
	int		i;
	char	**var;
	char	*inc;
	int		found;
	char	**env2;
	int 	k;

	if (!args[1])
		return (print_export(args, p, fd));
	var = ft_split(args[1], '=');
	inc = ft_strjoin(var[0], "=");
	if (!inc)
		exit(0);
	i = 0;
	k = 0;
	found = 0;
	while (p->env1[i])
	{
		if (ft_strncmp(p->env1[i], inc, ft_strlen(inc)) == 0)
		{
			// printf("env[%d]=%s, inc=%s, strlen=%ld\n", i, p->env1[i], inc, ft_strlen(inc));
			// printf("found the same\n");
			found = 1;
			p->env1[i] = ft_strjoin(inc, var[1]);
		}
		i++;
	}
	if (found == 0)
	{
		// printf("found=0\n");
		env2 = malloc(sizeof(char*) * (i + 2));
		i = 0;
		while (p->env1[i])
		{
			env2[i] = malloc(ft_strlen(p->env1[i]) + 1);
			while (p->env1[i][k])
			{
				env2[i][k] = p->env1[i][k];
				k++;
			}
			env2[i][k] = 0;
			k = 0; 
			i++;
		}
		if (var[1] == NULL)
		{
			env2[i] = inc;
			// printf("i=%d, inc=%s\n", i, inc);
		}
		else
		{
			env2[i] = ft_strjoin(inc, var[1]);
			// printf("env2[%d]=%s\n", i, env2[i]);
		}
		env2[i + 1] = 0;
		i = 0;
		while (p->env1[i])
		{
			//printf("free: environ[%d]=%s\n", i, p->env1[i]);
			free(p->env1[i]);
			//p->env1[i] = env2[i];
			i++;
		}
		//printf("freeing environ!\n");
		free(p->env1);
		p->env1 = env2;
	}
	return (1);
}

int		env(char **args, t_vars *p, int fd)
{
	int	i;

	i = 0;
	while (p->env1[i])
	{
		ft_putstr_fd(p->env1[i], fd);
		ft_putchar_fd('\n', fd);
		i++;
	}
	return (1);
}