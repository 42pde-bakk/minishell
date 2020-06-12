/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer <pde-bakk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/13 21:10:47 by peer          #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2020/06/12 17:26:03 by wbarendr      ########   odam.nl         */
=======
/*   Updated: 2020/06/12 17:37:37 by pde-bakk      ########   odam.nl         */
>>>>>>> 2348e2b2a4ac84f76ce6d66fc6dfc354e0483bc8
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> //pls remove when done
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"
# include "ft_printf.h"
# include <errno.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
extern int	errno;
int			g_ret;

extern char **environ;

typedef struct	s_vars
{
	char		**env1;
	int			ret;
	int			is_child;
	char		**paths;
	char		*home_path;
}				t_vars;

typedef struct	s_dup
{
	int			in;
	int			out;
	char		*input;
	char		*output;
	int			stdinbak;
	int			stdoutbak;
	int			trimmedlen;
}				t_dup;

int				cd(char **args, t_vars *p);
int				pwd();
void			argcheck(char **args, t_vars *p);
int				env(char **args, t_vars *p);
int				bubble_sort(char **arr);
int				unset_new(char **args, t_vars *p);
char			**split_quotes2(char *str);
void			ft_execute(char **args, t_vars *p);
int				print_env_var(char *args, t_vars *p, int fd);
void    		write_instant(char *str, int fd, t_vars *p);
char			**ft_split_q(char *s, char c);
int				main(void);

/*
** Utils
*/
int				ft_strcmp_equal(char *str1, char *str2);
char			*ft_strstrip(char *str, int i, int k);
int				get_next_line_q(int fd, char **line);
void			ft_putstr_fd_ret(char *str, int fd, t_vars *p);
void			remove_case(char **args);
void			block_ctrl_c(int sig);
void			block_ctrl_slash(int sig);
void			ft_putstr_fd_1(char *s, int fd);
int				find_equal(char *str);
char			*ft_strjoin_free(char *s1, char const *s2);
void			create_two_spaces(char **str);
char			*ft_strjoin_free_slash(char *s1, char const *s2, int n);
void			find_char(char *str, int *i, char d);
int				is_alpha_num(char c);
void			remove_quotes(char **args);
void			count_char2(int *i, int *co);
void			fill_char_c(char *str, char **new, int *i, int *n);
void			fill_char_e(char *str, char **new, int *i, int *n);
int				run_back_slash(char *str, int *index);
void			not_found(char *str);
void			get_environment2(char **env1, char *environ, int i);

/*
** Export
*/
int				check_valid_export(char *str);
int				export(char **args, t_vars *p);
char			**ft_split_equal(char *str);
int				find_match(char *env, char *new);
void			free_var(char **var, int *s);

/*
** Free_functions
*/
void			free_args(char **args);
void			free_line_cmds(char **cmds, char *line, int i);
void			free_arr_top_down(char **arr, int *i);
void			*ft_free_array(char **arr);
int				free_var_ret(char **var);

/*
** Gameloop
*/
char			*improve_line(char *line);
int				syntax_check(char *line);
char			**trimargs(char **args);
int				do_pipes_and_redirs(char **pipesplitcmds, int n, t_vars *p);
int				gameloop(t_vars *p, char *line);

/*
** Pipes and redirections
*/
void			minipipe(char **pipesplitcmds, int n,
						t_vars *p, char **trimmed);
void			redirect(char **args, t_dup *redirs);
void			reset_redirections(t_dup *redirs);

#endif