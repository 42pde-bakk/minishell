/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   trimming.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/12 17:36:03 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/06/17 16:23:18 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_str3join(char *a, char *b, char *c)
{
	char	*out;

	out = ft_calloc(ft_strlen(a) + ft_strlen(b) + ft_strlen(c) + 1,
			sizeof(char));
	if (out == NULL)
		return (out);
	ft_strlcpy(out, a, ft_strlen(a) + 1);
	ft_strlcpy(out + ft_strlen(a), b, ft_strlen(b) + 1);
	ft_strlcpy(out + ft_strlen(a) + ft_strlen(b), c, ft_strlen(c) + 1);
	return (out);
}

/*
** Checks if current arg isnt </>/>> and
** if either i == 0 or the previous argument isnt </>/>>
*/

int		trimcheck(char **args, int i)
{
	if ((ft_strncmp(args[i], "<", 2) != 0 && ft_strncmp(args[i], ">", 2) &&
	ft_strncmp(args[i], ">>", 3) != 0) && (i == 0 ||
	(ft_strncmp(args[i - 1], "<", 2) != 0 && ft_strncmp(args[i - 1], ">", 2)
	&& ft_strncmp(args[i - 1], ">>", 3) != 0)))
		return (1);
	else
		return (0);
}

char	**trimloop(char **args, char **out)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (args[i])
	{
		if (trimcheck(args, i) == 1)
		{
			out[len] = ft_strdup(args[i]);
			if (out[len] == NULL)
			{
				free_args(out);
				return ((char**)NULL);
			}
			len++;
		}
		i++;
	}
	return (out);
}

char	**trimargs(char **args)
{
	int		i;
	int		len;
	char	**out;

	i = 0;
	len = 0;
	while (args[i])
	{
		if (trimcheck(args, i) == 1)
			len++;
		i++;
	}
	i = 0;
	out = ft_calloc(len + 1, sizeof(char*));
	if (out == NULL)
		return (out);
	return (trimloop(args, out));
}

void	p_is_child(t_vars *p)
{
	if (p->is_child == 2)
		ft_putstr_fd("\x1b[34;01mQuit: 3\n\x1b[35;01mbash-3.3$ \x1b[31;37m", 1);
	if (p->is_child == 1 || p->is_child == 2)
	{
		g_ret = 0;
		p->is_child = 0;
	}
	else
		ft_putstr_fd("\x1b[35;01mbash-3.3$\x1b[31;37m ", 1);
}
