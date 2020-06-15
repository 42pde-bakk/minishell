/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bubblesort.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: wbarendr <wbarendr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 14:45:58 by wbarendr      #+#    #+#                 */
/*   Updated: 2020/06/15 18:16:31 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	same(char **arr, int *i)
{
	int		k;
	char	*temp;

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

void	later_in_alph(char **arr, int *i)
{
	char	*temp;

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

void	cpy_loop(char *env1, char **arr)
{
	int k;

	k = 0;
	while (env1[k])
	{
		(*arr)[k] = env1[k];
		k++;
	}
	(*arr)[k] = 0;
}

char	**make_cpy(char **env1)
{
	char	**arr;
	int		i;

	i = 0;
	while (env1[i])
		i++;
	arr = malloc(sizeof(char *) * (i + 1));
	if (arr == NULL)
		exit(1);
	arr[i] = 0;
	i = 0;
	while (env1[i])
	{
		arr[i] = malloc(ft_strlen(env1[i]) + 1);
		if (arr[i] == NULL)
			exit(1);
		cpy_loop(env1[i], &arr[i]);
		i++;
	}
	return (arr);
}

int		bubble_sort(char **env1, int fd)
{
	int		i;
	char	**arr;

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
	i = 0;
	while (arr[i])
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd_1(arr[i], fd);
		ft_putchar_fd('\n', fd);
		i++;
	}
	free_arr_top_down(arr, &i);
	return (0);
}
