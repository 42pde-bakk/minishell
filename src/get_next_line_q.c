/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_q.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: Wester <Wester@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/20 13:18:45 by Wester        #+#    #+#                 */
/*   Updated: 2020/05/26 15:47:29 by Wester        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_connect(char **line, char c)
{
	int i;
	char *tmp;

	i = 0;
	tmp = malloc(ft_strlen(*line) + 2);
	if (!tmp)
		return (NULL);
	while ((*line)[i])
	{
		tmp[i] = (*line)[i];
		i++;
	}
	tmp[i] = c;
	tmp[i + 1] = 0;
	free(*line);
	return (tmp);
}

int		check_line(char *line)
{
	int i;
	int quote;
	int single_quote;

	single_quote = 0;
	quote = 0;
	i = 0;
	while (line[i])
	{
		if (i > 0)
		{
			if (line[i] == '\"' && line[i - 1] != '\\' && single_quote % 2 == 0)
				quote++;
			else if (line[i] == '\'' && line[i - 1] != '\\' && quote % 2 == 0)
				single_quote++;
		}
		else if (line[i] == '\"' && single_quote % 2 == 0)
			quote++;
		else if (line[i] == '\'' && quote % 2 == 0)
			single_quote++;
		if (quote % 2 == 0 && single_quote % 2 == 0 && line[i] == '\n')
			return (1);
		if (line[i] == '\n' && line[i + 1] == 0)
			ft_putstr_fd("> ", 1);
		i++;
	}
	return (0);
}

char	*cut_line_break(char **line)
{
	char *new;
	int i;

	i = 0;
	new = malloc(ft_strlen(*line));
	if (new == NULL)
		return (NULL);
	while ((*line)[i] != '\n')
	{
		new[i] = (*line)[i];
		i++;
	}
	new[i] = 0;
	free(*line);
	return (new);	
}

int		get_next_line_q(int fd, char **line)
{
	char	buf[1];
	int		ret;

	*line = malloc(1);
	if (!(*line))
		return (-1);
	(*line)[0] = 0;
	while (1)
	{
		ret = read(fd, buf, 1);
		// printf("line: %s\n", *line);
		if (ret == -1 || (ret == 0 && (*line)[0] == 0))
			return (ret);
		if (ret != 0)
			*line = str_connect(line, buf[0]);
		if (!(*line))
			return (-1);
		if (buf[0] == '\n')
			if (check_line(*line))
				return (1);
		if (ft_strlen(*line) > 1)
		{
			if ((*line)[ft_strlen(*line) - 2] == '^' && (*line)[ft_strlen(*line) - 1] == 'C')
				return (1);
		}
	}
}
