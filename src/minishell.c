/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer <pde-bakk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 14:46:08 by wbarendr      #+#    #+#                 */
/*   Updated: 2020/06/17 16:22:37 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** If forked == 1, dont need to fork again in ft_execute.
*/

void	argcheck(char **args, t_vars *p, t_dup *redirs, int forked)
{
	int fd;

	fd = 1;
	if (redirs->out > 0)
		fd = redirs->out;
	if (args[0] == NULL)
		return ;
	else if (ft_strncmp(args[0], "echo", 5) == 0)
		p->ret = echo(args, p, fd);
	else if (ft_strncmp(args[0], "exit", 5) == 0)
		our_exit(args, p);
	else if (ft_strncmp(args[0], "pwd", 4) == 0)
		p->ret = pwd(fd);
	else if (ft_strncmp(args[0], "cd", 3) == 0)
		p->ret = cd(args, p);
	else if (ft_strncmp(args[0], "export", 7) == 0)
		p->ret = export(args, p, fd);
	else if (ft_strncmp(args[0], "env", 4) == 0)
		p->ret = env(args, p, fd);
	else if (ft_strncmp(args[0], "unset", 6) == 0 && args[1])
		p->ret = unset_new(args, p);
	else
		exec_checkifforked(args, p, redirs, forked);
}

void	fork_check(char **args, t_vars *p, t_dup *redirs)
{
	remove_case(&args[0]);
	if (redirs->in > 2 || redirs->out > 2)
	{
		if (fork() == 0)
		{
			argcheck(args, p, redirs, 1);
			exit(0);
		}
		else
		{
			p->pids++;
		}
	}
	else
		argcheck(args, p, redirs, 0);
	close_fd(redirs->in);
	close_fd(redirs->out);
}

void	get_path_home(t_vars *p, char **env1)
{
	int		i;
	char	*sub;

	i = 0;
	while (env1[i] && ft_strncmp(env1[i], "HOME=", 5) != 0)
		i++;
	if (env1[i] == NULL)
		return ;
	sub = ft_substr(env1[i], 5, ft_strlen(env1[i]) - 4);
	i = 0;
	p->home_path = malloc(ft_strlen(sub + 1) + 3);
	if (p->home_path == NULL)
	{
		free(sub);
		return ;
	}
	while (sub[i])
	{
		p->home_path[i] = sub[i];
		i++;
	}
	p->home_path[i] = '/';
	p->home_path[i + 1] = 0;
	free(sub);
}

char	**get_environment(t_vars *p, int i)
{
	char		**env1;
	extern char	**environ;

	write(1, "\e[1;1H\e[2J", 11);
	p->ret = 0;
	p->is_child = 0;
	while (environ[i])
		i++;
	env1 = ft_calloc(i + 1, sizeof(char *));
	if (env1 == NULL)
		exit(1);
	i = 0;
	while (environ[i])
	{
		env1[i] = malloc(ft_strlen(environ[i]) + 1);
		get_environment2(env1, environ[i], i);
		i++;
	}
	get_path_home(p, env1);
	return (env1);
}

int		main(void)
{
	char	*line;
	t_vars	p;

	p.env1 = get_environment(&p, 0);
	while (1)
	{
		p_is_child(&p);
		signal(SIGINT, block_ctrl_c);
		signal(SIGQUIT, block_ctrl_slash);
		if (!(get_next_line_q(0, &line)))
		{
			ft_dprintf(1, "\x1b[34;01m exit \x1b[0m\n");
			exit(0);
		}
		p.ret += g_ret;
		g_ret = 0;
		gameloop(&p, line);
	}
	return (0);
}
