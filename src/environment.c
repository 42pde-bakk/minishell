/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   environment.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer <pde-bakk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/03 14:44:12 by wbarendr      #+#    #+#                 */
/*   Updated: 2020/06/09 18:50:30 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_valid_export(char *str)
{
	int i;

	i = 0;
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
	{
		ft_dprintf(2, "-bash: export: `%s': %s\n", str, strerror(errno));
		// ft_putstr_fd("-bash: export: `", 2);
		// ft_putstr_fd(str, 2);
		// ft_putstr_fd("': not a valid identifier", 2);
		// write(2, "\n", 1);
		return (1);
	}
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && str[i] != '_' && !ft_isdigit(str[i]))
		{
			ft_dprintf(2, "-bash: export: `%s': %s\n", str, strerror(errno));
			// ft_putstr_fd("-bash: export: `", 2);
			// ft_putstr_fd(str, 2);
			// ft_putstr_fd("': not a valid identifier", 2);
			// write(2, "\n", 1);
			return (1);
		}
		i++;
	}
	return (0);
}

char	*fill_var_one(char *str)
{
	int		i;
	char	*temp;

	i = 0;
	while (str[i] != 0 && str[i] != '=')
		i++;
	temp = malloc(i + 1);
	if (temp == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		temp[i] = str[i];
		i++;
	}
	temp[i] = 0;
	return (temp);
}

char	*fill_var_two(char *str, char **var)
{
	int		i;
	int		k;
	char	*temp;

	i = 0;
	k = 0;
	while (str[i] != '=' && str[i] != 0)
		i++;
	if (!str[i])
		return (NULL);
	temp = malloc(ft_strlen(str) - i);
	if (temp == NULL)
	{
		free(var[0]);
		free(var);
		return (NULL);
	}
	while (str[k + 1 + i])
	{
		temp[k] = str[k + 1 + i];
		k++;
	}
	temp[k] = 0;
	return (temp);
}

char	**ft_split_equal(char *str)
{
	char	**var;

	var = malloc(sizeof(char *) * 2);
	if (var == NULL)
	{
		ft_dprintf(2, "malloc failed [ENOMEM]: %s\n", strerror(errno));
		return (NULL);
	}
	var[0] = fill_var_one(str);
	if (var[0] == NULL)
	{
		free(var);
		return (NULL);
	}
	var[1] = fill_var_two(str, var);
	if (var[0] == NULL)
		return (NULL);
	return (var);
}

int		find_match(char *env, char *new)
{
	int i;

	i = 0;
	if (!env || !new)
		return (0);
	while (new[i] == env[i] && new[i] && env[i])
	{
		if (new[i] != env[i])
			return (0);
		i++;
	}
	if (new[i] == 0 && (env[i] == 0 || env[i] == '='))
		return (1);
	return (0);
}
