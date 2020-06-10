/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer <pde-bakk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 15:42:29 by Wester        #+#    #+#                 */
/*   Updated: 2020/06/10 18:54:33 by Peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


char		*remove_start(char **args)
{
	int		i;
	char	*str;

	i = 0;
	if (!(args[0][0] == '.' || args[0][0] == '/'))
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

void		fill_paths(char *str, char **args, int k, t_vars *p)
{
	int i;

	i = 0;
	p->paths = ft_split(str + k, ':');
	while (p->paths[i])
	{
		p->paths[i] = ft_strjoin_free_slash(p->paths[i], args[0], 0);
		i++;
	}
	i = 0;
	while (p->paths[i])
	{
		execve(p->paths[i], args, NULL);
		i++;
	}
	free_args(p->paths);
}

void		get_paths(char **args, t_vars *p)
{
	int i;
	int k;

	k = 0;
	i = 0;
	while (p->env1[i])
	{
		// ft_dprintf(2, "p->env1[%d] = %s\n", i, p->env1[i]);
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

char		*ft_str3join(char *a, char *b, char *c)
{
	char	*out;

	out = ft_calloc(ft_strlen(a) + ft_strlen(b) + ft_strlen(c) + 1, sizeof(char));
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
	// dprintf(2, "substring = %s\n", sub);
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
	while (entries[i])
	{
		tmp = ft_str3join(entries[i], "/", args[0]);
		// dprintf(2, "tmp = %s, and stat(tmp) = %d\n", tmp, stat(tmp, &statstruct));
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
		dprintf(2, "abspath = %s, args[0] = %s,\n", abspath, args[0]);
		if (abspath && execve(abspath, args, p->env1) == -1)
			ft_dprintf(2, "abs. bash: %s: %s\n", args[0], strerror(errno));
		else if (!abspath && execve(args[0], args, p->env1) == -1)
			ft_dprintf(2, "!abs. bash: %s: %s\n", args[0], strerror(errno));
		p->is_child = 0;
		ft_dprintf(2, "errno = %d\n", errno);
		// not_found(args[0]);
		exit(127);
	}
	dprintf(2, "pid of %s is waiting for execve to finish\n", args[0]);
	waitpid(i, NULL, 0);
	dprintf(2, "%s 's execve is finished\n", args[0]);
	return_values(i, p);
}
