/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: Wester <Wester@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 14:20:00 by Wester        #+#    #+#                 */
/*   Updated: 2020/06/02 13:03:30 by wbarendr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_strcmp_equal(char *str1, char *str2)
{
	int i;

	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	if ((str1[i] == '=' && str2[i] == 0) || (str1[i] == 0 && str2[i] == 0))
		return (1);
	return (0);
}

void	remove_case(char **args)
{
	int i;

	i = 0;
	while ((*args)[i])
	{
		if ((*args)[i] >= 'A' && (*args)[i] <= 'Z')
			(*args)[i] += 32;
		i++;
	}
}

int		check_single_quote(char *str, int i)
{
	int ret;

	ret = 0;
	printf("i: %d\n", i);
	while (i >= 0)
	{
		if (str[i] == '\'')
			ret++;
		i--;
	}
	printf("ret: %d\n", ret);
	return (ret % 2);
}

void	ft_putstr_fd_ret(char *str, int fd, t_vars *p)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			ft_putnbr_fd(p->ret, fd);
			i += 2;
		}
		else
		{ 
			write(fd, &str[i], 1);
			i++;
		}
	}
}

void		block_ctrl_c(int sig)
{
	//signal(sig, SIG_IGN);
	//kill(0, sig);
	ft_putstr_fd("\nminishell> ", 1);
	sig = 0;
	// exit(0);
}

void	block_ctrl_slash(int sig)
{
	// signal(sig, SIG_IGN);
	//kill(0, sig);
	sig = 0;
	// ft_putstr_fd("Quit: 3\n", 1);
}

void	ft_putstr_fd_1(char *s, int fd)
{
	int i;
	int once;

	once = 0;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		if (s[i] == '=' && once == 0)
		{
			once = 1;
			write(fd, "\"", 1);
		}
		i++;
	}
	if (once == 1)
		write(fd, "\"", 1);
}

int		find_equal(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin_free(char *s1, char const *s2)
{
	int		i;
	int		n;
	char	*join;

	i = 0;
	n = 0;
	if (s1 == 0 || s2 == 0)
		return (0);
	join = (char*)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (join == NULL)
		return (NULL);
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[n])
	{
		join[i] = s2[n];
		i++;
		n++;
	}
	join[i] = '\0';
	free(s1);
	return (join);
}

char	*ft_strjoin_free_slash(char *s1, char const *s2)
{
	int		i;
	int		n;
	char	*join;

	i = 0;
	n = 0;
	if (s1 == 0 || s2 == 0)
		return (0);
	join = (char*)malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (join == NULL)
		return (NULL);
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	join[i] = '/';
	i++;
	while (s2[n])
	{
		join[i] = s2[n];
		i++;
		n++;
	}
	join[i] = '\0';
	free(s1);
	return (join);
}