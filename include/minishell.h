/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/13 21:10:47 by peer          #+#    #+#                 */
/*   Updated: 2020/05/27 13:14:51 by Wester        ########   odam.nl         */
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
# include <signal.h>
# include <limits.h>
extern int errno;

extern char **environ;

typedef struct	s_vars
{
	char		**env1;
	int			ret;
	//int			child_nr;
	int			is_child;
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


int				env(char **args, t_vars *p);
int				bubble_sort(char **arr);
int				unset_new(char **args, t_vars *p);
char			**split_quotes2(char *str);
void			ft_execute(char **args, t_vars *p);
int				print_env_var(char *args, t_vars *p, int fd);
void    		write_instant(char *str, int fd, t_vars *p);
int				main(void);

//utils
int				ft_strcmp_equal(char *str1, char *str2);
char			*ft_strstrip(char *str, char c);
int				get_next_line_q(int fd, char **line);
void			ft_putstr_fd_ret(char *str, int fd, t_vars *p);
void			remove_case(char **args);
void			block_ctrl_c(int sig);
void			block_ctrl_slash(int sig);
void			ft_putstr_fd_1(char *s, int fd);
int				find_equal(char *str);
char			*ft_strjoin_free(char *s1, char const *s2);
//export
int				check_valid_export(char *str);
int				export(char **args, t_vars *p);
char			**ft_split_equal(char *str);
int				find_match(char *env, char *new);
void			free_var(char **var, int *s);


#endif