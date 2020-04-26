/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/13 21:13:16 by peer          #+#    #+#                 */
/*   Updated: 2020/04/26 19:58:04 by peer          ########   odam.nl         */
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
}

void	redirect(char **args, t_vars *p, t_dup *redir)
{
	int i, in = 0, out = 0;
	char output[64], input[64];

	i = 0;
	while (args[i])
	{
		if (ft_strncmp(args[i], "<", 2) == 0)
		{
			args[i] = NULL; //makes it NULL to ensure that commands won't read it as input
			ft_strlcpy(input, args[i + 1], ft_strlen(args[i + 1]));
			in = 2;
		}
		if (ft_strncmp(args[i], ">", 2) == 0) //still need to do ">>"
		{
			args[i] = NULL;
			ft_strlcpy(output, args[i + 1], ft_strlen(args[i + 1]) + 1);
			out = 2;
		}
		i++;
	}
	if (in)
	{
		redir->infilefd = open(input, O_RDONLY, 0);
		if (redir->infilefd < 0)
		{
			ft_putstr_fd("couldnt open input file\n", 2);
			exit(0);
		}
		redir->savestdin = dup(0);
		// dup2 copies content of fd0 in input of preceding file
		redir->duppedin = dup2(redir->infilefd, 0);
		printf("infilefd = %d, stdin saved at %d, duppedin = %d\n", redir->infilefd, redir->savestdin, redir->duppedin);
		close(redir->infilefd); //Necessary apparently, all this: source=https://stackoverflow.com/questions/11515399/implementing-shell-in-c-and-need-help-handling-input-output-redirection
	}
	if (out)
	{
		redir->outfilefd = open(output, O_CREAT | O_TRUNC | O_RDWR, 0644);
		dprintf(2, "outfilefd = %d\n", redir->outfilefd);
		if (redir->outfilefd < 0)
		{
			ft_putstr_fd("couldnt open output file\n", 2);
			exit(0);
		}
		// else
		// {
		// 	int writetest = write(redir->outfilefd, "blimp", sizeof("blimp"));
		// 	dprintf(2, "writing blimp to fd=%d returns %d\n", redir->outfilefd, writetest);
		// }
		redir->savestdout = dup(1);
//		printf("savestdout = %d\n", redir->savestdout);
		// close(1);
		redir->duppedout = dup2(redir->outfilefd, 1);
//		dprintf(2, "calling dup2(%d, %d) gives %d\n", redir->outfilefd, 1, redir->duppedout);
		close(redir->outfilefd);
	}
	argcheck(args, p);
	int test0, test1;
	if (in)
	{
		test0 = dup2(redir->savestdin, redir->duppedin);
		if (test0 < 0)
			{
				dprintf(2, "ma che cazzo\n");
				exit(0);
			}
	}
	if (out)
	{
		test1 = dup2(redir->savestdout, redir->duppedout);
		if (test1 < 0)
			{
				dprintf(2, "ma che cazzo\n");
				exit(0);
			}
	}
}

void	argcheck(char **args, t_vars *p)
{
	if (args[0] == NULL)
		return ;
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
	if (ft_strncmp(args[0], "unset", 6) == 0)
		unset_new(args, p);
}

char 	**get_environment(void)
{
	int	i;
	char **env1;
	int k;

	k = 0;
	i = 0;
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
//			argcheck(args, &p);
			redirect(args, &p, &redir);
			i++;
		}
		if (cmds)
			free(cmds);
		if (line)
			free(line);
	}
	return (0);
}
