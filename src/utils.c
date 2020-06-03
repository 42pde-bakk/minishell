/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: Wester <Wester@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/16 14:20:00 by Wester        #+#    #+#                 */
/*   Updated: 2020/06/03 19:20:16 by wbarendr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_putstr_fd_1(char *s, int fd)
{
	int i;
	int once;

	once = 0;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		if (s[i] == '=' && once == 0)
		{
			once = 1;
			write(fd, "\"", 1);
		}
		i++;
	}
	if (once == 1)
		write(fd, "\"", 1);
}

char		*ft_strjoin_free(char *s1, char const *s2)
{
	int		i;
	int		n;
	char	*join;

	i = 0;
	n = 0;
	if (s1 == 0 || s2 == 0)
		return (0);
	join = (char*)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (join == NULL)
		return (NULL);
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[n])
	{
		join[i] = s2[n];
		i++;
		n++;
	}
	join[i] = '\0';
	free(s1);
	return (join);
}

char		*ft_strjoin_free_slash(char *s1, char const *s2, int n)
{
	int		i;
	char	*join;

	i = 0;
	if (s1 == 0 || s2 == 0)
		return (0);
	join = (char*)malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (join == NULL)
		return (NULL);
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	join[i] = '/';
	i++;
	while (s2[n])
	{
		join[i] = s2[n];
		i++;
		n++;
	}
	join[i] = '\0';
	free(s1);
	return (join);
}

void		create_two_spaces(char **str)
{
	int		i;
	char	*new;

	i = 0;
	new = malloc(ft_strlen(*str) + 3);
	new[0] = ' ';
	new[1] = ' ';
	while ((*str)[i])
	{
		new[i + 2] = (*str)[i];
		i++;
	}
	new[i + 2] = 0;
	*str = new;
}

void		remove_quotes(char **args)
{
	int i;

	i = 0;
	while (args[i])
	{
		args[i] = ft_strstrip(args[i], 0, 0);
		i++;
	}
}
