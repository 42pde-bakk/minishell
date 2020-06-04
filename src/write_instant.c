/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_instant.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: Wester <Wester@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/03 17:57:26 by Wester        #+#    #+#                 */
/*   Updated: 2020/06/04 14:35:57 by wbarendr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	single_quote(char *str, int *i, int fd)
{
	(*i)++;
	while (str[*i] != '\'')
	{
		write(fd, &str[*i], 1);
		(*i)++;
	}
}

void	found_env_var(char *str, int *i, int fd, t_vars *p)
{
	int k;
	int l;

	l = 0;
	k = 0;
	while (p->env1[k])
	{
		while (p->env1[k][l] == str[*i + l] && p->env1[k][l])
			l++;
		if (p->env1[k][l] == '=' && !is_alpha_num(str[*i + l]))
		{
			l++;
			while (p->env1[k][l])
			{
				write(fd, &p->env1[k][l], 1);
				l++;
			}
			return ;
		}
		l = 0;
		k++;
	}
}

void	double_quote(char *str, int *i, int fd, t_vars *p)
{
	(*i)++;
	while (!(str[*i] == '\"' && !run_back_slash(str, i)) && str[*i] != 0)
	{
		if (str[*i] == '$' && is_alpha_num(str[*i + 1]) &&
		!run_back_slash(str, i))
		{
			(*i)++;
			if (str[*i] == '?')
				ft_putnbr_fd(p->ret, fd);
			else
				found_env_var(str, i, fd, p);
			while (is_alpha_num(str[*i]))
				(*i)++;
		}
		else
		{
			if (!(str[*i] == '\\' && !run_back_slash(str, i) && (str[*i + 1]
			== '\"' || str[*i + 1] == '\\')))
				write(fd, &str[*i], 1);
			(*i)++;
		}
	}
}

void	found_env(char *str, int fd, t_vars *p, int *i)
{
	(*i)++;
	if (str[*i] == '?')
		ft_putnbr_fd(p->ret, fd);
	else
		found_env_var(str, i, fd, p);
	while (is_alpha_num(str[*i]))
		(*i)++;
}

void	write_instant(char *str, int fd, t_vars *p)
{
	int i;

	i = 2;
	create_two_spaces(&str);
	while (str[i])
	{
		if (str[i] == '\'' && !run_back_slash(str, &i))
			single_quote(str, &i, fd);
		else if (str[i] == '\"' && !run_back_slash(str, &i))
			double_quote(str, &i, fd, p);
		else if (str[i] == '$' && is_alpha_num(str[i + 1]) &&
		!run_back_slash(str, &i))
			found_env(str, fd, p, &i);
		else if (!(str[i] == '\\' && !run_back_slash(str, &i) && (str[i + 1]
		== '\"' || str[i + 1] == '\\' || str[i + 1] == '\'')))
			write(fd, &str[i], 1);
		if (str[i] != 0)
			i++;
	}
	free(str);
}
