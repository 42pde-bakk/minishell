/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 14:50:52 by peer          #+#    #+#                 */
/*   Updated: 2020/04/29 14:08:52 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_set_values(t_dup *redir)
{
	redir->check[0] = 0;
	redir->check[1] = 0;
	redir->savestdin = 0;
	redir->savestdout = 1;
}

int	redirect(char **args, t_dup *redir)
{
	int			i;
	char		output[64];
	char		input[64];

	i = 0;
	redir_set_values(redir);
	while (args[i])
	{
		if (ft_strncmp(args[i], "<", 2) == 0)
		{
			args[i] = NULL; //makes it NULL to ensure that commands won't read it as input
			ft_strlcpy(input, args[i + 1], ft_strlen(args[i + 1]));
			redir->check[0] = 2;
		}
		if (ft_strncmp(args[i], ">", 2) == 0 || ft_strncmp(args[i], ">>", 3) == 0) //still need to do ">>"
		{
			ft_strlcpy(output, args[i + 1], ft_strlen(args[i + 1]) + 1);
			if (ft_strncmp(args[i], ">>", 3) == 0)
				redir->check[1] = 3;
			else
				redir->check[1] = 2;
			args[i] = NULL;
		}
//		dprintf(2, "i = %d & args[i] = %s, args[i+1] = %s,  redir->check[] = %d, %d\n", i, args[i], args[i+1], redir->check[0], redir->check[1]);
		i++;
	}
	if (redir->check[0])
	{
		redir->infilefd = open(input, O_RDONLY, 0);
		if (redir->infilefd < 0)
		{
			ft_putstr_fd("couldnt open input file\n", 2);
			exit(0);
		}
		redir->savestdin = dup(0);
		redir->duppedin = dup2(redir->infilefd, 0);
//		printf("infilefd = %d, stdin saved at %d, duppedin = %d\n", redir->infilefd, redir->savestdin, redir->duppedin);
		close(redir->infilefd); //Necessary, all this: source=https://stackoverflow.com/questions/11515399/implementing-shell-in-c-and-need-help-handling-input-output-redirection
	}
	if (redir->check[1])
	{
		if (redir->check[1] == 3)
			redir->outfilefd = open(output, O_CREAT | O_APPEND | O_RDWR, 0644);
		else
			redir->outfilefd = open(output, O_CREAT | O_TRUNC | O_RDWR, 0644);
		if (redir->outfilefd < 0)
		{
			ft_putstr_fd("couldnt open output file\n", 2);
			exit(0);
		}
		redir->savestdout = dup(1);
//		dprintf(2, "savestdout = %d\n", redir->savestdout);
		redir->duppedout = dup2(redir->outfilefd, 1);
		close(redir->outfilefd);
	}
//	dprintf(2, "end of redirect(), returning %d + %d = %d\n", redir->check[0], redir->check[1], redir->stat + redir->check[0] + redir->check[1]);
	return (redir->check[0] + redir->check[1]);
}

void	reset_redirect(t_dup *redir)
{
	int test0;
	int test1;

//	dprintf(2, "reset: check[0]=%d, check[1]=%d\n", redir->check[0], redir->check[1]);
	if (redir->check[0])
	{
		test0 = dup2(redir->savestdin, redir->duppedin);
		if (test0 < 0)
			{
				dprintf(2, "resetting stdin failed\n");
				exit(0);
			}
		redir->check[0] = 0;
	}
	if (redir->check[1])
	{
		test1 = dup2(redir->savestdout, redir->duppedout);
		if (test1 < 0)
			{
				dprintf(2, "resetting stdout failed\n");
				exit(0);
			}
		redir->check[1] = 0;
	}
}
