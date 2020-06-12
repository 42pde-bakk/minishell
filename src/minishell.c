/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer <pde-bakk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 14:46:08 by wbarendr      #+#    #+#                 */
/*   Updated: 2020/06/12 16:20:29 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		echo(char **args, t_vars *p, int fd)
{
	int i;

	i = 1;
	if (args[1] && ft_strncmp(args[1], "-n", 3) == 0)
		i = 2;
	while (args[i])
	{
		write_instant(args[i], fd, p);
		i++;
		if (args[i] != 0)
			ft_putchar_fd(' ', fd);
	}
	if (!args[1] || (args[1] && ft_strncmp(args[1], "-n", 3) != 0))
		ft_putchar_fd('\n', fd);
	return (0);
}

void	argcheck(char **args, t_vars *p)
{
	remove_case(&args[0]);
	if (args[0] == NULL)
		return ;
	else if (ft_strncmp(args[0], "echo", 5) == 0)
		p->ret = echo(args, p, 1);
	else if (ft_strncmp(args[0], "exit", 5) == 0)
		exit(0);
	else if (ft_strncmp(args[0], "pwd", 4) == 0)
		p->ret = pwd();
	else if (ft_strncmp(args[0], "cd", 3) == 0)
		p->ret = cd(args);
	else if (ft_strncmp(args[0], "export", 7) == 0)
		p->ret = export(args, p);
	else if (ft_strncmp(args[0], "env", 4) == 0)
		p->ret = env(args, p);
	else if (ft_strncmp(args[0], "unset", 6) == 0 && args[1])
		p->ret = unset_new(args, p);
	else
		ft_execute(args, p);
}

char	**get_environment(t_vars *p, int i)
{
	char	**env1;
	int		k;

	k = 0;
	write(1, "\e[1;1H\e[2J", 11);
	p->ret = 0;
	p->is_child = 0;
	while (environ[i])
		i++;
	env1 = ft_calloc(i + 1, sizeof(char *));
	if (env1 == NULL)
		return (NULL);
	i = 0;
	while (environ[i])
	{
		env1[i] = malloc(ft_strlen(environ[i]) + 1);
		if (env1[i] == NULL)
		{
			free_args(env1);
			return (NULL);
		}
		while (environ[i][k])
		{
			env1[i][k] = environ[i][k];
			k++;
		}
		env1[i][k] = 0;
		k = 0;
		i++;
	}
	return (env1);
}

int		main(void)
{
	char	*line;
	t_vars	p;

	p.env1 = get_environment(&p, 0);
	while (1)
	{
		if (p.is_child == 2)
			ft_putstr_fd("\x1b[34;01mQuit: 3\nbash-3.3$ \x1b[0m", 1);
		if (p.is_child == 1 || p.is_child == 2)
		{
			g_ret = 0;
			p.is_child = 0;
		}
		else
			ft_putstr_fd("\x1b[35;01mbash-3.3$\x1b[31;37m ", 1);
		signal(SIGINT, block_ctrl_c);
		signal(SIGQUIT, block_ctrl_slash);
		if (!(get_next_line_q(0, &line)))
		{
			write(1, "\x1b[31;01mexit\x1b[0m\n", 5);
			exit(0);
		}
		p.ret += g_ret;
		g_ret = 0;
		gameloop(&p, line);
	}
	return (0);
}
