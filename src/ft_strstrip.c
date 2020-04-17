/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strstrip.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: Wester <Wester@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/17 14:35:27 by Wester        #+#    #+#                 */
/*   Updated: 2020/04/17 14:55:05 by Wester        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			count_char(char *str, char c)
{
	int i;
	int co;

	i = 0;
	co = 0;
	while (str[i])
	{
		if (str[i] == c)
			co++;
		i++;
	}
	return (i - co);
}

char 		*ft_strstrip(char *str, char c)
{
	int		i;
	int		k;
	char	*new_str;

	new_str = malloc(count_char(str, c) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	k = 0;
	while (str[i])
	{
		if (!(str[i] == c) && !(str[i] == '\\'))
		{
			new_str[k] = str[i];
			k++;
		}
		i++;
		if (str[i] == c && str[i - 1] == '\\')
		{
			new_str[k] = str[i];
			k++;
		}
	}
	return (new_str);
}