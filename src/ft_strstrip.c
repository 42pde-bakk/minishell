/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strstrip.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: Wester <Wester@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/17 14:35:27 by Wester        #+#    #+#                 */
/*   Updated: 2020/06/03 16:04:26 by wbarendr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			find_match1(char *str, int *i)
{
	int		ret;

	ret = 0;
	if (str[*i] == '\'')
	{
		(*i)++;
		while (str[*i] != '\'' && str[*i] != 0)
			(*i)++;
	}
	else if (str[*i] == '\"')
	{
		(*i)++;
		while (str[*i] != '\"' && str[*i] != 0)
			(*i)++;
	}
	(*i)++;
	return (ret);
}

int			count_char(char *str, int i, int co)
{
	while (str[i])
	{
		if (i == 0)
		{
			if (str[i] == '\"' || str[i] == '\'')
			{
				co += 2;
				co -= find_match1(str, &i);
				continue ;
			}
		}
		else if ((str[i] == '\"' || str[i] == '\'') && str[i - 1] != '\\')
		{
			co += 2;
			co -= find_match1(str, &i);
			continue ;
		}
		else if (str[i] == '\"' || str[i] == '\'')
			co++;
		else if (str[i] == '\\' && str[i - 1] == '\\')
			count_char2(&i, &co);
		if (str[i] != 0)
			i++;
	}
	return (i - co);
}

void		fill_new(char **new_str, char *str, int *i, int *k)
{
	if (str[*i] == '\'')
	{
		(*i)++;
		while (str[*i] != '\'' && str[*i] != 0)
		{
			(*new_str)[*k] = str[*i];
			(*k)++;
			(*i)++;
		}
	}
	else if (str[*i] == '\"')
	{
		(*i)++;
		while (str[*i] != '\"' && str[*i] != 0)
		{
			(*new_str)[*k] = str[*i];
			(*k)++;
			(*i)++;
		}
	}
	(*i)++;
}

void		ft_strstrip2(char *str, char *new_str, int *i, int *k)
{
	if (str[*i] == '\\' && str[*i + 1] == '\\')
	{
		new_str[*k] = str[*i];
		(*i) += 2;
		(*k)++;
	}
	else if (str[*i] == '\\' && str[*i + 1] != '\\')
		(*i)++;
	if (str[*i] != '\\' && str[*i] != 0)
	{
		new_str[*k] = str[*i];
		(*k)++;
		(*i)++;
	}
}

char		*ft_strstrip(char *str, int i, int k)
{
	char	*new_str;

	new_str = malloc(count_char(str, 0, 0) + 1);
	if (!new_str)
		exit(0);
	while (str[i])
	{
		if (i == 0)
		{
			if (str[i] == '\'' || str[i] == '\"')
			{
				fill_new(&new_str, str, &i, &k);
				continue ;
			}
		}
		else if ((str[i] == '\'' || str[i] == '\"') && str[i - 1] != '\\')
		{
			fill_new(&new_str, str, &i, &k);
			continue ;
		}
		ft_strstrip2(str, new_str, &i, &k);
	}
	new_str[k] = 0;
	free(str);
	return (new_str);
}
