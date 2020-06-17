/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer <pde-bakk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 15:42:29 by Wester        #+#    #+#                 */
/*   Updated: 2020/06/17 13:03:07 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void		close_ifnot_and_dup(t_vars *p, t_dup *redirs)
{
	int i;

	i = 0;
	while (p->pipes[i])
	{
		if (p->pipes[i][0] > 2 && p->pipes[i][0] != redirs->in)
		{
			close(p->pipes[i][0]);
		}
		if (p->pipes[i][1] > 2 && p->pipes[i][1] != redirs->out)
		{
			close(p->pipes[i][1]);
		}
		i++;
	}
	if (redirs->in > 0 && dup2(redirs->in, 0) < 0)
		exit(1);
	if (redirs->out > 0 && dup2(redirs->out, 1) < 0)
		exit(1);
}

void		ft_execute(char **args, t_vars *p, t_dup *redirs)
{
	char		*abspath;
	struct stat	statstr;

	abspath = NULL;
	remove_quotes(args);
	if (fork() == 0)
	{
		close_ifnot_and_dup(p, redirs);
		get_abspath(&abspath, p, args);
		if (abspath && execve(abspath, args, p->env1) == -1)
			ft_dprintf(2, "bash: %s: %s\n", args[0], strerror(errno));
		else if (!abspath && args[0][0] != '.' && stat(args[0], &statstr) < 0)
			ft_dprintf(2, "bash: %s: command not found\n", args[0]);
		else if (!abspath && execve(args[0], args, p->env1) == -1)
			ft_dprintf(2, "bash: %s: %s\n", args[0], strerror(errno));
		p->is_child = 0;
		exit(127);
	}
	else
		p->pids++;
	close_fd(redirs->in);
	close_fd(redirs->out);
}
