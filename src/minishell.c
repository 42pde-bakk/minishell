/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/13 21:13:16 by peer          #+#    #+#                 */
/*   Updated: 2020/04/13 22:37:32 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		pwd(char **args)
{
	char	buf[10240];
	char	*ptr;

	ptr = getcwd(buf, 10240);
	ft_putstr_fd(ptr, 1);
	ft_putchar_fd('\n', 1);
}

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

void	argcheck(char **args)
{
	if (ft_strncmp(args[0], "echo", 5) == 0)
		echo(args);
	if (ft_strncmp(args[0], "exit", 5) == 0)
		exit(0);
	if (ft_strncmp(args[0], "pwd", 4) == 0)
		pwd(args);
}

int		main(int argc, char **argv)
{
	int		status;
	char	*line;
	char	**args;

	status = 1;
	while (status)
	{
		args[0] = NULL;
		ft_putstr_fd("peershell> ", 2);
		status = get_next_line(0, &line);
		if (line)
			args = ft_split(line, ' ');
		printf("status=%d, line=%s \n", status, line);
		if (args[0])
			argcheck(args);
		if (line)
			free(line);
	}
	
}