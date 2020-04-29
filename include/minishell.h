/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/13 21:10:47 by peer          #+#    #+#                 */
/*   Updated: 2020/04/29 16:58:07 by Wester        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> //pls remove when done
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"
# include <errno.h>
# include <sys/wait.h>
extern int errno;

extern char **environ;

typedef struct	s_vars
{
	char		**env1;
	int			ret;
}				t_vars;

typedef struct	s_dup
{
	int			check[2];
	int			savestdin;
	int			savestdout;
	int			infilefd;
	int			outfilefd;
	int			duppedin;
	int			duppedout;
}				t_dup;

int				cd(char **args);
int				pwd();

int				redirect(char **args, t_dup *redir);
void			reset_redirect(t_dup *redir);

void			argcheck(char **args, t_vars *p);

int				export(char **args, t_vars *p);
int				env(char **args, t_vars *p);
char			**bubble_sort(char **arr);
void			unset_new(char **args, t_vars *p);
char			**split_quotes(char *str);

//utils
int				ft_strcmp_equal(char *str1, char *str2);
char			*ft_strstrip(char *str, char c);
int				get_next_line_q(int fd, char **line);
void			ft_execute(char **args, t_vars *p);

#endif