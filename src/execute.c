/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Wester <Wester@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 15:42:29 by Wester        #+#    #+#                 */
/*   Updated: 2020/05/02 11:59:21 by Wester        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char        *remove_start(char **args)
{
	int i;
	char *str;

	i = 0;
	if (!(args[0][0] == '.' && args[0][1] == '/'))
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

void        ft_execute(char **args, t_vars *p)
{
	int i;
	int test;

	i = 0;
	args[0] = remove_start(args);
	if (fork() == 0)
	{
		test = execve(args[0], args, NULL);
		// printf("test: %d\n", test);
		exit(127);
	}
	wait(&i);
	// printf("test - i: %d\n", i);
	// p->child_nr = i;
	if (WIFEXITED(i))
		p->ret = WEXITSTATUS(i);
	if (WIFSIGNALED(i))
	{
		p->ret = WTERMSIG(i);
		if (p->ret == 2)
			p->ret = 130;
		if (p->ret == 3)
			p->ret = 131;
	}
}