/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/12 14:39:26 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/06/13 23:45:45 by peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		quote_check(int *singlequote, int *doublequote, char c)
{
	if (c == '\'')
		(*singlequote)++;
	else if (c == '\"')
		(*doublequote)++;
	if (*singlequote % 2 == 0 && *doublequote % 2 == 0)
		return (1);
	return (0);
}

int		syntax_check_redirs(char *line, int *i, char *syntax)
{
	if (line[*i] == '>' || line[*i] == '<')
	{
		(*i)++;
		if (line[*i] == '>' && line[*i] == '>')
			(*i)++;
		while (line[*i] == ' ')
			(*i)++;
		if (ft_isalnum(line[*i]) == 0)
		{
			if (line[*i] == '\n')
				return (ft_dprintf(2, "%s `%s\'\n", syntax, "newline"));
			return (ft_dprintf(2, "%s `%c\'\n", syntax, line[*i]));
		}
	}
	return (0);
}

int		syntax_check(char *line)
{
	int		i;
	char	*syntax;
	int		quotes[2];

	ft_bzero(&quotes, sizeof(quotes));
	syntax = "bash: syntax error near unexpected token";
	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '|')
		return (ft_dprintf(2, "%s `|\'\n", syntax));
	while (line[i])
	{
		while (quote_check(&quotes[0], &quotes[1], line[i]) == 0)
			i++;
		if (line[i] == ';' && line[i + 1] == ';')
			return (ft_dprintf(2, "%s `;;\'\n", syntax));
		if (syntax_check_redirs(line, &i, syntax) > 0)
			return (2);
		i++;
	}
	return (0);
}

char	*addspaces(char *out, char *line)
{
	int i;
	int n;
	int q[3];

	i = 0;
	n = 0;
	ft_bzero(&q, sizeof(q));
	while (line[i])
	{
		q[2] = quote_check(&q[0], &q[1], line[i]);
		if (q[2] && (line[i] == '<' || (line[i] == '>' && line[i - 1] != '>')))
		{
			out[n] = ' ';
			n++;
		}
		out[n] = line[i];
		n++;
		if (q[2] && (line[i] == '<' || (line[i] == '>' && line[i + 1] != '>')))
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
	int		quotes[2];

	i = 0;
	ft_bzero(&quotes, sizeof(quotes));
	redircount = 0;
	while (line[i])
	{
		if (quote_check(&quotes[0], &quotes[1], line[i]))
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
