/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: Wester <Wester@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 14:20:00 by Wester        #+#    #+#                 */
/*   Updated: 2020/04/16 17:42:00 by Wester        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ft_strcmp_equal(char *str1, char *str2)
{
    int i;

    i = 0;
    while (str1[i] && str2[i])
    {
        if (str1[i] != str2[i])
            return (0);
        i++;
    }
    if (str1[i] == '=')
        return (1);
    return (0);
}