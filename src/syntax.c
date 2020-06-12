/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/12 14:39:26 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/06/12 17:23:15 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		syntax_check_redirs(char *line, int *i)
{
	if (line[*i] == '>' || line[*i] == '<')
	{
		(*i)++;
		if (line[*i] == '>' && line[*i] == '>')
			(*i)++;
		while (line[*i] == ' ')
			(*i)++;
		if (ft_isalnum(line[*i]) == 0)
			return (1);
	}
	return (0);
}

int		syntax_check(char *line)
{
	int		i;
	char	*syntax;

	syntax = "bash: syntax error near unexpected token";
	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '|')
		return (dprintf(2, "%s \'|\'\n", syntax));
	while (line[i])
	{
		if (line[i] == ';' && line[i + 1] == ';')
			return (dprintf(2, "%s \';;\'\n", syntax));
		if (syntax_check_redirs(line, &i) == 1)
			return (dprintf(2, "%s \'%c\'\n", syntax, line[i]));
		i++;
	}
	return (0);
}

char	*addspaces(char *out, char *line)
{
	int i;
	int n;

	i = 0;
	n = 0;
	while (line[i])
	{
		if (line[i] == '<' || (line[i] == '>' && line[i - 1] != '>'))
		{
			out[n] = ' ';
			n++;
		}
		out[n] = line[i];
		n++;
		if (line[i] == '<' || (line[i] == '>' && line[i + 1] != '>'))
		{
			out[n] = ' ';
			n++;
		}
		i++;
	}
	return (out);
}

char	*improve_line(char *line)
{
	char	*out;
	int		redircount;
	int		i;

	i = 0;
	redircount = 0;
	while (line[i])
	{
		if (line[i] == '<' || (line[i] == '>' && line[i + 1] != '>'))
			redircount++;
		i++;
	}
	out = ft_calloc(i + 1 + 2 * redircount, sizeof(char));
	if (out == NULL)
	{
		free(line);
		return (out);
	}
	out = addspaces(out, line);
	free(line);
	return (out);
}
