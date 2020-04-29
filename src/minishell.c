/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/13 21:13:16 by peer          #+#    #+#                 */
/*   Updated: 2020/04/29 15:41:33 by Wester        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
extern int errno;

void	echo(char **args)
{
	char	*new;

	if (args[1] == NULL)
		ft_putchar_fd('\n', 1);
	else if (ft_strncmp(args[1], "-n", 3) == 0 && args[2])
	{
		new = ft_strstrip(args[2], '\"');
		ft_putstr_fd(new, 1);
		free(new);
	}
	else if (args[1])
	{
		new = ft_strstrip(args[1], '\"');
		ft_putstr_fd(new, 1);
		ft_putchar_fd('\n', 1);
		free(new);
	}
	// int i = 0;
	// while (args[i])
	// {
	// 	dprintf(2, "echo test: args[%d] = %s\n", i, args[i]);
	// 	i++;
	// }
}

void	argcheck(char **args, t_vars *p)
{
	if (args[0] == NULL)
		return ;
	if (ft_strncmp(args[0], "echo", 5) == 0)
		echo(args);
	else if (ft_strncmp(args[0], "exit", 5) == 0)
		exit(0);
	else if (ft_strncmp(args[0], "pwd", 4) == 0)
		pwd();
	else if (ft_strncmp(args[0], "cd", 3) == 0)
		cd(args);
	else if (ft_strncmp(args[0], "export", 7) == 0)
		export(args, p);
	else if (ft_strncmp(args[0], "env", 4) == 0)
		env(args, p);
	else if (ft_strncmp(args[0], "unset", 6) == 0)
		unset_new(args, p);
	else 
		ft_execute(args, p);
}

char 	**get_environment(void)
{
	int	i;
	char **env1;
	int k;

	k = 0;
	i = 0;
	write(1, "\e[1;1H\e[2J", 11);
	while (environ[i])
		i++;
	env1 = malloc(sizeof(char *) * (i + 1));
	env1[i] = 0;
	i = 0;
	while (environ[i])
	{
		env1[i] = malloc(ft_strlen(environ[i]));
		while (environ[i][k])
		{
			env1[i][k] = environ[i][k];
			k++;
		}
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

	p.env1 = get_environment();
	status = 1;
	(void)argc;
	(void)argv;
	while (status)
	{
		i = 0;
		args = (char**)NULL;
		cmds = (char**)NULL;
		ft_putstr_fd("peershell> ", 1);
		status = get_next_line_q(0, &line);
		if (line)
			cmds = ft_split(line, ';');
		while (cmds[i])
		{
			args = split_quotes(cmds[i]);
			redirect(args, &redir);
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
