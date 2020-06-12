/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer <pde-bakk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 15:42:29 by Wester        #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2020/06/12 14:29:11 by wbarendr      ########   odam.nl         */
=======
/*   Updated: 2020/06/12 15:59:36 by pde-bakk      ########   odam.nl         */
>>>>>>> 2348e2b2a4ac84f76ce6d66fc6dfc354e0483bc8
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

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

char		*ft_str3join(char *a, char *b, char *c)
{
	char	*out;

	out = ft_calloc(ft_strlen(a) + ft_strlen(b) + ft_strlen(c) + 1,
			sizeof(char));
	if (out == NULL)
		return (out);
	ft_strlcpy(out, a, ft_strlen(a) + 1);
	ft_strlcpy(out + ft_strlen(a), b, ft_strlen(b) + 1);
	ft_strlcpy(out + ft_strlen(a) + ft_strlen(b), c, ft_strlen(c) + 1);
	return (out);
}

char		**get_pathentries(t_vars *p)
{
	char		**out;
	int			i;
	char		*sub;

	i = 0;
	while (p->env1[i] && ft_strncmp(p->env1[i], "PATH=", 5) != 0)
		i++;
	if (p->env1[i] == NULL)
		return ((char**)NULL);
	sub = ft_substr(p->env1[i], 5, ft_strlen(p->env1[i]) - 4);
	if (sub == NULL)
		return (NULL);
	out = ft_split_q(sub, ':');
	free(sub);
	return (out);
}

void		get_abspath(char **abspath, t_vars *p, char **args)
{
	int			i;
	char		*tmp;
	struct stat	statstruct;
	char		**entries;

	i = 0;
	entries = get_pathentries(p);
	while (entries && entries[i])
	{
		tmp = ft_str3join(entries[i], "/", args[0]);
		if (tmp == NULL)
			return ;
		if (stat(tmp, &statstruct) != -1)
		{
			*abspath = tmp;
			return ;
		}
		free(tmp);
		i++;
	}
}

void		ft_execute(char **args, t_vars *p)
{
	int		i;
	char	*abspath;

	i = 0;
	abspath = NULL;
	remove_quotes(args);
	if (fork() == 0)
	{
		get_abspath(&abspath, p, args);
		if (abspath && execve(abspath, args, p->env1) == -1)
			ft_dprintf(2, "bash: %s: %s\n", args[0], strerror(errno));
		else if (!abspath && execve(args[0], args, p->env1) == -1)
			ft_dprintf(2, "bash: %s: %s\n", args[0], strerror(errno));
		p->is_child = 0;
		exit(127);
	}
	waitpid(i, &i, 0);
	return_values(i, p);
}
