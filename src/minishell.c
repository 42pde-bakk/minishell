/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/13 21:13:16 by peer          #+#    #+#                 */
/*   Updated: 2020/05/06 10:29:47 by Wester        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
extern int errno;

int		echo(char **args, t_vars *p, int fd)
{
	int i;

	// if (args[1] == NULL)
	// 	ft_putchar_fd('\n', 1);
	// else if (ft_strncmp(args[1], "-n", 3) == 0 && args[2])
	// {
	// 	// if (args[2][0] == '$' && args[2][1] != '?')
	// 	// 	return (print_env_var(args[2], p, 1));
	// 	new = ft_strstrip(args[i], '\"');
	// 	ft_putstr_fd_ret(new, 1, p);
	// 	free(new);
	// }
	i = 1;
	if (args[1] && ft_strncmp(args[1], "-n", 3) == 0)
		i = 2;
	while (args[i])
	{
		// printf("arg[0]: %s\n", args[i]);
		//print_echo(args[1]);
		// if (args[1][0] == '$' && args[1][1] != '?')
		// 	print_env_var(args[1], p, 1);
		// else 
		// {
			write_instant(args[i], fd, p);
			// new = ft_strstrip(new, '\"', p);
			// ft_putstr_fd_ret(new, 1, p);
			// free(new);
		// }
		i++;
		if (args[i] != 0)
			ft_putchar_fd(' ', fd);
	}
	if (args[1] && ft_strncmp(args[1], "-n", 3) != 0)
		ft_putchar_fd('\n', fd);
	return (0);
}

void	argcheck(char **args, t_vars *p)
{
	remove_case(&args[0]);
	// printf("arg: %s-", args[0]);
	// if (fork() == 0)
	// {
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
		else if (ft_strncmp(args[0], "unset", 6) == 0)
			p->ret = unset_new(args, p);
		else
			ft_execute(args, p);
		// exit(0);
	// }
	// wait(&i);
	// if (WIFEXITED(i))
		// p->ret = WEXITSTATUS(i);
}

char 	**get_environment(t_vars *p)
{
	int	i;
	char **env1;
	int k;

	k = 0;
	i = 0;
	write(1, "\e[1;1H\e[2J", 11);
	p->ret = 0;
	while (environ[i])
		i++;
	env1 = malloc(sizeof(char *) * (i + 1));
	env1[i] = NULL;
	i = 0;
	while (environ[i])
	{
		env1[i] = malloc(ft_strlen(environ[i]) + 1);
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

int		main(int argc, char **argv)
{
	int		status;
	char	*line;
	char	**args;
	char	**cmds;
	int		i;
	t_vars	p;
	t_dup	redir;

	p.child_nr = 0;
	p.env1 = get_environment(&p);
	status = 1;
	(void)argc;
	(void)argv;
	while (status)
	{
		i = 0;
		args = (char**)NULL;
		cmds = (char**)NULL;
		ft_putstr_fd("peershell> ", 1);
		signal(SIGINT, block_ctrl_c);
		signal(SIGQUIT, block_ctrl_slash);
		status = get_next_line_q(0, &line);
		if (status == 0)
		{
			write(1, "logout\n", 7);
			exit(0);
		}
		if (line) 
			cmds = ft_split(line, ';');
		while (cmds[i])
		{
			args = split_quotes2(cmds[i]);
			redirect(args, &redir);
			if (args[0])
				argcheck(args, &p);
			reset_redirect(&redir);
			i++;
		}
		if (cmds)
			free(cmds);
		if (line)
			free(line);
	}
	return (0);
}
