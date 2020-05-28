/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_quotes2.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: Wester <Wester@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 10:30:06 by Wester        #+#    #+#                 */
/*   Updated: 2020/05/28 13:42:16 by Wester        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		find_char(char *str, int *i, char d)
{
	(*i)++;
	if (d == '\"')
	{
		while (str[*i] && (!(str[*i] == d && (str[*i - 1] != '\\' ||
		(str[*i - 1] == '\\' && str[*i - 2] == '\\')))))
			(*i)++;
		(*i)++;
		return ;
	}
	while (str[*i] && str[*i] != d)
		(*i)++;
	(*i)++;
}

int			ft_words(char *str, char c, char e, int i)
{
	int words;

	words = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i])
		words++;
	while (str[i])
	{
		if (str[i] == c)
			find_char(str, &i, c);
		else if (str[i] == e)
			find_char(str, &i, e);
		else if (!(str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)) && str[i] != 0)
			i++;
		else if (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		{
			while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
				i++;
			if (str[i])
				words++;
		}
	}
	return (words);
}

char        **ft_free(char **arr, int count)
{
	while (count >= 0)
	{
		free(arr[count]);
		count--;
	}
	free(arr);
	return (NULL);
}

void		fill_char_c(char *str, char **new, int *i, int *n)
{
	(*new)[*n] = str[*i];
	(*n)++;
	(*i)++;
	while (str[*i] != '\'')
	{
		(*new)[*n] = str[*i];
		(*n)++;
		(*i)++;
	}
	(*new)[*n] = str[*i];
	(*n)++;
	(*i)++;
}

void		fill_char_e(char *str, char **new, int *i, int *n)
{
	(*new)[*n] = str[*i];
	(*n)++;
	(*i)++;
	while (str[*i] && (!(str[*i] == '\"' && (str[*i - 1] != '\\' ||
		(str[*i - 1] == '\\' && str[*i - 2] == '\\')))))
	{
		(*new)[*n] = str[*i];
		(*n)++;
		(*i)++;
	}
	(*new)[*n] = str[*i];
	(*n)++;
	(*i)++;
}

void		fill_word(char **new, char *str, int i)
{
	int n;

	n = 0;
	while (!(str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
	{
		if (str[i] == '\'')
			fill_char_c(str, new, &i, &n);
		else if (str[i] == '\"')
			fill_char_e(str, new, &i, &n);
		else
		{
			(*new)[n] = str[i];
			i++;
			n++;
		}
	}
	(*new)[n] = 0;
}

char		*find_word_quote(char *str, int *i, char c, char e)
{
	int		save_index;
	char	*new_word;

	save_index = *i;
	while (!(str[*i] == ' ' || (str[*i] >= 9 && str[*i] <= 13)))
	{
		if (str[*i] == c)
			find_char(str, i, c);
		else if (str[*i] == e)
			find_char(str, i, e);
		else
			(*i)++;
	}
	new_word = malloc(*i - save_index + 1);
	if (new_word == NULL) 
		return (NULL);
	fill_word(&new_word, str, save_index);
	return (new_word);
}

char 		**split_quotes2(char *str)
{
	int i;
	int k;
	char **arr;

	k = 0;
	i = 0;
	// printf("str: %s\n", str);
	arr = malloc(sizeof(char *) * (ft_words(str, '\'', '\"', 0) + 1));
	// printf("str: %d\n", ft_words(str, '\'', '\"', 0));
	while (str[i])
	{
		while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			i++;
		if (!str[i])
			break ;
		arr[k] = find_word_quote(str, &i, '\'', '\"');
		// printf("arr[k]: %s\n", arr[k]);
		// if (arr[k] == NULL)
		// 	return (ft_free(arr, k));
		k++;
	}
	arr[k] = 0;
	return (arr);
}