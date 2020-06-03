/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: wbarendr <wbarendr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 19:14:16 by wbarendr      #+#    #+#                 */
/*   Updated: 2020/06/03 19:23:10 by wbarendr      ########   odam.nl         */
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

int		is_alpha_num(char c)
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

void	count_char2(int *i, int *co)
{
	(*i)++;
	(*co)++;
}
