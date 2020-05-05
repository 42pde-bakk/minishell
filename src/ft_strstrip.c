/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strstrip.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: Wester <Wester@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/17 14:35:27 by Wester        #+#    #+#                 */
/*   Updated: 2020/05/05 15:22:12 by Wester        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// int			is_alpha_num(char c)
// {
// 	if (c >= 'A' && c <= 'Z')
// 		return (1);
// 	if (c >= 'a' && c <= 'z')
// 		return (1);
// 	if (c >= '0' && c <= '9')
// 		return (1);
// 	if (c == '?');
// 		return (1);
// 	if (c == 95)
// 		return (1);
// 	return (0);
// }

// int		check_end_path(char c)
// {
// 	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
// 		return 0;
// 	if (c == 95)
// 		return 0;
// 	return (1);
// }

// int 	find_env_var(char *args, int *i, t_vars *p)
// {
// 	int k;
// 	int l;
// 	int save_l;

// 	k = 0;
// 	l = 0;
// 	while (p->env1[k])
// 	{
// 		while (p->env1[k][l] == args[*i + 1 + l] && p->env1[k][l])
// 			l++;
// 		if (p->env1[k][l] == '=' && check_end_path(args[*i + 1 + l]))
// 		{
// 			l++;
// 			save_l = l;
// 			while (p->env1[k][l])
// 				l++;
// 			(*i) += save_l - 1;
// 			return (l - save_l);
// 		}
// 		l = 0;
// 		k++;
// 	}
// 	while (check_end_path(args[*i]) == 0)
// 		(*i)++;
// 	return (0);
// }

// int		find_match(char *str, int *i, t_vars *p)
// {
// 	int ret;

// 	ret = 0;
// 	if (str[*i] == '\'')
// 	{
// 		(*i)++;
// 		while (str[*i] != '\'' && str[*i] != 0)
// 			(*i)++;
// 	}
// 	else if (str[*i] == '\"')
// 	{
// 		(*i)++;
// 		while (str[*i] != '\"' && str[*i] != 0)
// 		{
// 			(*i)++;
// 			if (str[*i] == '$' && is_alpha_num(str[*i + 1]))
// 				ret += find_env_var(str, &i, p);
// 		}
// 	}
// 	(*i)++;
// 	return (ret);
// }

// /* int			find_match_dollar(char *str, int i, t_vars *p);
// {
// 	int save_i;
// 	int count_quotes;

// 	count_quotes = 0;
// 	save_i = i;
// 	while(i >= 0)
// 	{
// 		if (str[i] == '\'')
// 			count_quotes++;
// 		i--;
// 	}
// 	if (count_quotes % 2 == 0)
// }

// int			count_env_var(char *str, t_vars *p)
// {
// 	int i;
// 	int co;

// 	if (str[0] == '$')
// 		find_match_dollar(str, 0);
// 	if (str[0] != 0)
// 		if (str[1] == '$' && str[0] != '\\')
// 			find_match_dollar(str, 1);
// 	i = 1;
// 	while (str[i])
// 	{
// 		i++;
// 		if (str[i] == '$' && (str[i - 1] != '\\' || (str[i - 1] == '\\' && str[i - 2] == '\\')))
// 			find_match_dollar(str, i);
// 	}
// } */

// int			count_char(char *str, char c, char e, t_vars *p)
// {
// 	int i;
// 	int co;

// 	i = 0;
// 	co = 0;
// 	while (str[i])
// 	{
// 		if (i == 0)
// 		{
// 			if (str[i] == c || str[i] == e)
// 			{
// 				co += 2;
// 				co -= find_match(str, &i, p);
// 				continue ;
// 			}
// 		}
// 		else if ((str[i] == c || str[i] == e) && str[i - 1] != '\\')
// 		{
// 			co += 2;
// 			co -= find_match(str, &i, p);
// 			continue ;
// 		}
// 		else if (str[i] == c || str[i] == e)
// 			co++;
// 		else if (str[i] == '\\' && str[i - 1] == '\\')
// 		{
// 			i++;
// 			co++;
// 		}
// 		if (str[i] != 0)
// 		{
// 			if (str[i] == '$' && is_alpha_num(str[i + 1]))
// 				co -= find_env_var(str, &i, p);
// 			else
// 				i++;
// 		}
// 	}
// 	//count_env_var(str);
// 	// printf("i: %i num: %d\n", i, i - co);
// 	return (i - co);
// }

// void		fill_new(char **new_str, char *str, int *i, int *k)
// {
// 	if (str[*i] == '\'')
// 	{
// 		(*i)++;
// 		while (str[*i] != '\'' && str[*i] != 0)
// 		{
// 			(*new_str)[*k] = str[*i];
// 			(*k)++;
// 			(*i)++;
// 		}
// 	}
// 	else if (str[*i] == '\"')
// 	{
// 		(*i)++;
// 		while (str[*i] != '\"' && str[*i] != 0)
// 		{
// 			(*new_str)[*k] = str[*i];
// 			(*k)++;
// 			(*i)++;
// 		}
// 	}
// 	(*i)++;	
// }

// char		*last_strip_slash(char **str)
// {
// 	int i;
// 	int co;
// 	char *new_str;

// 	co = 0;
// 	i = 0;
// 	while ((*str)[i])
// 	{
// 		if ((*str)[i] == '\\' && (*str)[i + 1] == '\\')
// 		{
// 			i += 2;
// 			co++;
// 		}
// 		else
// 			 i++;
// 	}
// 	new_str = malloc(i - co + 1);
// 	i = 0;
// 	co = 0;
// 	while ((*str)[i])
// 	{
// 		if ((*str)[i] == '\\' && (*str)[i + 1] == '\\')
// 		{
// 			new_str[co] = (*str)[i];
// 			i += 2;
// 			co++;
// 		}
// 		else
// 		{
// 			new_str[co] = (*str)[i];
// 			i++;
// 			co++;
// 		}
// 	}
// 	new_str[co] = 0;
// 	free(*str);
// 	return (new_str);
// }

// char 		*ft_strstrip(char *str, char c, t_vars *p)
// {
// 	int		i;
// 	int		k;
// 	char	*new_str;

// 	// printf("str; %s\n", str);
// 	new_str = malloc(count_char(str, c, '\'', p) + 1);
// 	if (!new_str)
// 		return (NULL);
// 	i = 0;
// 	k = 0;
// 	while (str[i])
// 	{
// 		if (i == 0)
// 		{
// 			if (str[i] == '\'' || str[i] == '\"')
// 			{
// 				fill_new(&new_str, str, &i, &k);
// 				continue ;
// 			}
// 		}
// 		else if ((str[i] == '\'' || str[i] == '\"') && str[i - 1] != '\\')
// 		{
// 			fill_new(&new_str, str, &i, &k);
// 			continue ;
// 		}
// 		if (str[i] == '\\' && str[i + 1] == '\\')
// 		{
// 			new_str[k] = str[i];
// 			i += 2;
// 			k++;
// 		}
// 		else if (str[i] == '\\' && str[i + 1] != '\\')
// 			i++;
// 		if (str[i] != '\\' && str[i] != 0)
// 		{
// 			new_str[k] = str[i];
// 			k++;
// 			i++;
// 		}
// 	}
// 	// printf("new1: %s\n", new_str);
// 	new_str[k] = 0;
// 	// free(str);
// 	//new_str = last_strip_slash(&new_str);
// 	return (new_str);
// }