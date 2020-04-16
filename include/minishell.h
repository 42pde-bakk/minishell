/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/13 21:10:47 by peer          #+#    #+#                 */
/*   Updated: 2020/04/16 16:32:17 by Wester        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> //pls remove when done
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# include "get_next_line.h"
# include "libft.h"
extern char **environ;

typedef struct  s_vars
{
	char        **env1;
}               t_vars;

int		cd(char **args);
int		pwd(void);

int     export(char **args, t_vars *p);
int		env(char **args, t_vars *p);
char    **bubble_sort(char **arr);
void	unset_new(char **args, t_vars *p);

//utils
int     ft_strcmp_equal(char *str1, char *str2);

#endif