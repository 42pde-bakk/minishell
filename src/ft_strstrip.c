/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strstrip.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: Wester <Wester@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/17 14:35:27 by Wester        #+#    #+#                 */
/*   Updated: 2020/04/20 22:47:42 by Wester        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		find_match(char *str, int *i, char c, char e)
{
	if (str[*i] == c)
	{
		(*i)++;
		while (str[*i] != c && str[*i] != 0)
			(*i)++;
	}
	else if (str[*i] == e)
	{
		(*i)++;
		while (str[*i] != e && str[*i] != 0)
			(*i)++;
	}
	(*i)++;
}

int			count_char(char *str, char c, char e)
{
	int i;
	int co;

	i = 0;
	co = 0;
	while (str[i])
	{
		if (i == 0)
		{
			if (str[i] == c || str[i] == e)
			{
				co += 2;
				find_match(str, &i, c, e);
				continue ;
			}
		}
		else if ((str[i] == c || str[i] == e) && str[i - 1] != '\\')
		{
			co += 2;
			find_match(str, &i, c, e);
			continue ;
		}
		else if (str[i] == c || str[i] == e)
			co++;
		else if (str[i] == '\\' && str[i - 1] == '\\')
		{
			i++;
			co++;
		}
		if (str[i] != 0)
			i++;
	}
	printf("i: %i num: %d\n", i, i - co);
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

char		*last_strip_slash(char **str)
{
	int i;
	int co;
	char *new_str;

	co = 0;
	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\\' && (*str)[i + 1] == '\\')
		{
			i += 2;
			co++;
		}
		else
			 i++;
	}
	new_str = malloc(i - co + 1);
	i = 0;
	co = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\\' && (*str)[i + 1] == '\\')
		{
			new_str[co] = (*str)[i];
			i += 2;
			co++;
		}
		else
		{
			new_str[co] = (*str)[i];
			i++;
			co++;
		}
	}
	new_str[co] = 0;
	free(*str);
	return (new_str);
}

char 		*ft_strstrip(char *str, char c)
{
	int		i;
	int		k;
	char	*new_str;

	printf("str; %s\n", str);
	new_str = malloc(count_char(str, c, '\'') + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	k = 0;
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
		if (str[i] == '\\' && str[i + 1] == '\\')
		{
			new_str[k] = str[i];
			i += 2;
			k++;
		}
		else if (str[i] == '\\' && str[i + 1] != '\\')
			i++;
		if (str[i] != '\\' && str[i] != 0)
		{
			new_str[k] = str[i];
			k++;
			i++;
		}
	}
	printf("new1: %s\n", new_str);
	new_str[k] = 0;
	free(str);
	new_str = last_strip_slash(&new_str);
	return (new_str);
}