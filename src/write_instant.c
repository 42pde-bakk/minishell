/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_instant.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: Wester <Wester@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/03 17:57:26 by Wester        #+#    #+#                 */
/*   Updated: 2020/05/15 12:49:46 by Wester        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_two_spaces(char **str)
{
	int		i;
	char	*new;
	
	i = 0;
	new = malloc(ft_strlen(*str) + 3);
	new[0] = ' ';
	new[1] = ' ';
	while ((*str)[i])
	{
		new[i + 2] = (*str)[i];
		i++;
	}
	new[i + 2] = 0;
	//free(*str);
	*str = new;
}

void	single_quote(char *str, int *i, int fd)
{
	(*i)++;
	while (str[*i] != '\'')
	{
		write(fd, &str[*i], 1);
		(*i)++;
	}
}

int			is_alpha_num(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	if (c == '?' || c == '!' || c == '@' || c == '#' || c == '*' || c == '$')
		return (1);
	if (c == '_')
		return (1);
	return (0);
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
				//write(fd, "-", 1);
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
	while (str[*i] != '\"')
	{
 		if (str[*i] == '$' && is_alpha_num(str[*i + 1]) && (str[*i - 1] != '\\' || (str[*i - 1] == '\\' && str[*i - 2] == '\\')))
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
			write(fd, &str[*i], 1);
			(*i)++;
		}
	}
}

void    write_instant(char *str, int fd, t_vars *p)
{
	int i;

	i = 2;
	create_two_spaces(&str);
	// printf("\nstr: %s -- i: %d -- strlen_i %zu\n", str, i, ft_strlen(str));
	while (str[i])
	{
		if (str[i] == '\'' && (str[i - 1] != '\\' || (str[i - 1] == '\\' &&
		str[i - 2] == '\\')))
			single_quote(str, &i, fd);
		else if (str[i] == '\"' && (str[i - 1] != '\\' || (str[i - 1] == '\\'
		&& str[i - 2] == '\\')))
			double_quote(str, &i, fd, p);
		else if (str[i] == '$' && is_alpha_num(str[i + 1]) && (str[i - 1] != '\\' || (str[i - 1] == '\\'
		&& str[i - 2] == '\\')))
		{
			i++;
			if (str[i] == '?')
				ft_putnbr_fd(p->ret, fd);
			else
				found_env_var(str, &i, fd, p);
			while (is_alpha_num(str[i]))
				i++;
		}
		else if (str[i] != '\\' || (str[i] == '\\' && str[i - 1] == '\\' &&
		str[i - 2] != '\\'))
			write(fd, &str[i], 1);
		// printf("\nstr: %s -- i: %d -- strlen_i %zu\n", str, i, ft_strlen(str));
		if (str[i] != 0)
			i++;
		// write(1, "-", 1);
	}
	free(str);
}