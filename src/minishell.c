/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/13 21:13:16 by peer          #+#    #+#                 */
/*   Updated: 2020/04/14 18:43:12 by Wester        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char **args)
{
	int		i;
	char	*new;

	i = 0;
	if (ft_strncmp(args[1], "-n", 3) == 0 && args[2])
	{
		new = ft_strtrim(args[2], "\"");
		ft_putstr_fd(new, 1);
		free(new);
	}
	else if (args[1])
	{
		new = ft_strtrim(args[1], "\"");
		ft_putstr_fd(new, 1);
		ft_putchar_fd('\n', 1);
		free(new);
	}
}

/* 	char	*argv[] = {"text", "en2", "test", NULL};
	char	*argv2[] = {NULL};
	
	execve("./hello", argv, argv2);
 */
void	argcheck(char **args, t_vars *p)
{
	if (ft_strncmp(args[0], "echo", 5) == 0)
		echo(args);
	if (ft_strncmp(args[0], "exit", 5) == 0)
		exit(0);
	if (ft_strncmp(args[0], "pwd", 4) == 0)
		pwd();
	if (ft_strncmp(args[0], "cd", 3) == 0)
		cd(args);
	if (ft_strncmp(args[0], "export", 7) == 0)
		export(args, p);
	if (ft_strncmp(args[0], "env", 4) == 0)
		env(args, p);
}

char 	**get_environment(void)
{
	int	i;
	char **env1;

	i = 0;
	while (environ[i])
		i++;
	env1 = malloc(sizeof(char *) * (i + 1));
	env1[i] = 0;
	i = 0;
	while (environ[i])
	{
		env[i] = malloc(ft_strlen(environ[i]) wehebhwedhwvdwwd)
		env1[i] = environ[i];
		i++;
	}
	return (env1);
}

int		main(int argc, char **argv)
{
	int		status;
	char	*line;
	char	**args;
	t_vars	p;
	
	p.env1 = get_environment();
	status = 1;
	while (status)
	{
		args = (char**)NULL;
		ft_putstr_fd("peershell> ", 1);
		status = get_next_line(0, &line);
		if (line)
			args = ft_split(line, ' ');
		if (args[0])
			argcheck(args, &p);
		if (line)
			free(line);
	}
}