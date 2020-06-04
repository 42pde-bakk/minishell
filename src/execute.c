/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Wester <Wester@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 15:42:29 by Wester        #+#    #+#                 */
/*   Updated: 2020/06/04 15:57:59 by wbarendr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*remove_start(char **args)
{
	int		i;
	char	*str;

	i = 0;
	if (!(args[0][0] == '.' && args[0][1] == '/'))
		return (args[0]);
	str = malloc(ft_strlen(args[0]) - 1);
	if (str == NULL)
		exit(errno);
	while (args[0][i + 2])
	{
		str[i] = args[0][i + 2];
		i++;
	}
	str[i] = 0;
	free(args[0]);
	return (str);
}

void		fill_paths(char *str, char *args, int k, t_vars *p)
{
	int i;

	i = 0;
	p->paths = ft_split(str + k, ':');
	while (p->paths[i])
	{
		p->paths[i] = ft_strjoin_free_slash(p->paths[i], args, 0);
		i++;
	}
}

void		get_paths(char *args, t_vars *p)
{
	int i;
	int k;

	k = 0;
	i = 0;
	while (p->env1[i])
	{
		if (ft_strcmp_equal(p->env1[i], "PATH"))
		{
			while (p->env1[i][k] && p->env1[i][k - 1] != '=')
				k++;
			if (p->env1[i][k])
				fill_paths(p->env1[i], args, k, p);
			break ;
		}
		i++;
	}
}

void		return_values(int i, t_vars *p)
{
	if (WIFEXITED(i))
		p->ret = WEXITSTATUS(i);
	if (WIFSIGNALED(i))
	{
		p->ret = WTERMSIG(i);
		if (p->ret == 2)
		{
			p->ret = 130;
			p->is_child = 1;
		}
		if (p->ret == 3)
		{
			p->ret = 131;
			p->is_child = 2;
		}
	}
}

void		ft_execute(char **args, t_vars *p)
{
	int i;
	int k;

	k = 0;
	i = 0;
	remove_quotes(args);
	args[0] = remove_start(args);
	if (fork() == 0)
	{
		execve(args[0], args, NULL);
		get_paths(args[0], p);
		while (p->paths[k])
		{
			execve(p->paths[k], args, NULL);
			k++;
		}
		free_args(p->paths);
		p->is_child = 0;
		not_found(args[0]);
		exit(127);
	}
	wait(&i);
	return_values(i, p);
}
