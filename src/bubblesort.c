/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bubblesort.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 16:24:27 by peer          #+#    #+#                 */
/*   Updated: 2020/04/14 22:41:34 by Wester        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    same(char **arr, int *i)
{
    int k;
    char *temp;
    
    k = 0;
    while (arr[*i][k] == arr[*i + 1][k] && arr[*i][k] != 0)
        k++;
    if (arr[*i][k] > arr[*i + 1][k])
    {
        temp = arr[*i];
        arr[*i] = arr[*i + 1];
        arr[*i + 1] = temp;
    }
    (*i)++;
}

void    later_in_alph(char **arr, int *i)
{
    char *temp;

    while (arr[*i][0] > arr[*i + 1][0])
    {
        temp = arr[*i];
        arr[*i] = arr[*i + 1];
        arr[*i + 1] = temp;
        (*i)++;
        if (arr[*i + 1] == 0)
            break ;
    }
    (*i) = 0; 
}

char    **make_cpy(char **env1)
{
    char **arr;
    int i;
    int k;

    k = 0;
    i = 0;
    while (env1[i])
        i++;
    arr = malloc(sizeof(char *) * (i + 1));
    arr[i] = 0;
    i = 0;
    while (env1[i])
    {
        arr[i] = malloc(ft_strlen(env1[i]) + 1);
        while (env1[i][k])
        {
            arr[i][k] = env1[i][k];
            k++;
        }
        k = 0;
        i++;
    }
    return (arr);
}

char    **bubble_sort(char **env1)
{
    int i;
    char **arr;
    i = 0;

    arr = make_cpy(env1);
    while (arr[i + 1])
    {
        if (arr[i][0] > arr[i + 1][0])
            later_in_alph(arr, &i);
        else if (arr[i][0] == arr[i + 1][0])
            same(arr, &i);
        else 
            i++;
    }
    return (arr);
}
