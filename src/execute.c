/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Wester <Wester@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 15:42:29 by Wester        #+#    #+#                 */
/*   Updated: 2020/04/30 12:00:10 by Wester        ########   odam.nl         */
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

void        ft_execute(char **args)
{
	//int i;

	args[0] = remove_start(args);
	//if (fork() == 0)
	//{
		// stat(args[0],)
		// p->ret = "./args[0]"
	execve(args[0], args, NULL);
	//}
	//wait(&i);
	//if (WIFEXITED(i))
	//	p->ret = WEXITSTATUS(i);
	// printf("ret: %d\n", p->ret);
}