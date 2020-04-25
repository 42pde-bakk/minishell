/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/13 21:10:47 by peer          #+#    #+#                 */
/*   Updated: 2020/04/25 17:42:04 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> //pls remove when done
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# include "libft.h"
extern char **environ;

typedef struct  s_vars
{
	char        **env1;
}               t_vars;

int				cd(char **args);
int				pwd(int fd);

int     		export(char **args, t_vars *p, int fd);
int				env(char **args, t_vars *p, int fd);
char	 	  	**bubble_sort(char **arr);
void			unset_new(char **args, t_vars *p);
char			**split_quotes(char *str);

//utils
int			    ft_strcmp_equal(char *str1, char *str2);
char 			*ft_strstrip(char *str, char c);
int				get_next_line_q(int fd, char **line);

#endif