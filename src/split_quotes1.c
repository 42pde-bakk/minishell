/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_quotes1.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: wbarendr <wbarendr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 19:02:07 by wbarendr      #+#    #+#                 */
/*   Updated: 2020/06/03 19:06:32 by wbarendr      ########   odam.nl         */
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

int			ft_words(char *s, int words, int i)
{
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i])
		words++;
	while (s[i])
	{
		if (s[i] == '\'' && (s[i - 1] != '\\' || (s[i - 1] == '\\' &&
		s[i - 2] == '\\')))
			find_char(s, &i, '\'');
		else if (s[i] == '\"' && (s[i - 1] != '\\' || (s[i - 1] == '\\'
		&& s[i - 2] == '\\')))
			find_char(s, &i, '\"');
		else if (!(s[i] == ' ' || (s[i] >= 9 && s[i] <= 13)) && s[i] != 0)
			i++;
		else if (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		{
			while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
				i++;
			if (s[i])
				words++;
		}
	}
	return (words);
}

void		fill_word(char **new, char *str, int i)
{
	int n;

	n = 0;
	while (!(str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)) && str[i])
	{
		if (str[i] == '\'' && (str[i - 1] != '\\' || (str[i - 1] == '\\'
		&& str[i - 2] == '\\')))
			fill_char_c(str, new, &i, &n);
		else if (str[i] == '\"' && (str[i - 1] != '\\' || (str[i - 1] ==
		'\\' && str[i - 2] == '\\')))
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
	while (!(str[*i] == ' ' || (str[*i] >= 9 && str[*i] <= 13)) && str[*i])
	{
		if (str[*i] == c && (str[*i - 1] != '\\' || (str[*i - 1] == '\\' &&
		str[*i - 2] == '\\')))
			find_char(str, i, c);
		else if (str[*i] == e && (str[*i - 1] != '\\' || (str[*i - 1] == '\\'
		&& str[*i - 2] == '\\')))
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

char		**split_quotes2(char *str)
{
	int		i;
	int		k;
	char	**arr;

	k = 0;
	i = 0;
	arr = malloc(sizeof(char *) * (ft_words(str, 0, 0) + 1));
	while (str[i])
	{
		while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			i++;
		if (!str[i])
			break ;
		arr[k] = find_word_quote(str, &i, '\'', '\"');
		k++;
	}
	arr[k] = 0;
	return (arr);
}
