/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_quotes2.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: Wester <Wester@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 10:30:06 by Wester        #+#    #+#                 */
/*   Updated: 2020/06/03 19:02:41 by wbarendr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
