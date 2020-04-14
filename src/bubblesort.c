/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bubblesort.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: peer <peer@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 16:24:27 by peer          #+#    #+#                 */
/*   Updated: 2020/04/14 17:49:37 by peer          ########   odam.nl         */
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

char    **bubble_sort(char **arr)
{
    int i;
    char *temp;
    
    i = 0;
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