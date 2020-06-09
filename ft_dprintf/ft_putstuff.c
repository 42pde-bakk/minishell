/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstuff.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/04 17:26:41 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/06/09 17:35:07 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_strlen_peer(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		i++;
	}
	return (i);
}

void	ft_putchar_flags(char c, int fd, t_map *map, int check)
{
	if (check == 1 && map->width > 0)
	{
		map->width--;
		while (map->min == 0 && map->width > 0)
		{
			if (map->zero == 0)
				ft_putchar_flags(' ', fd, map, 0);
			else
				ft_putchar_flags('0', fd, map, 0);
			map->width--;
		}
	}
	write(fd, &c, 1);
	map->size++;
	while (check == 1 && map->min == 1 && map->width > 0)
	{
		ft_putchar_flags(' ', fd, map, 0);
		map->width--;
	}
}

void	ft_putstr_flags(char *s, int fd, t_map *map, int check)
{
	int	i;

	i = 0;
	if (check == 1)
		ft_flagfiller(fd, map, s);
	while (s[i] && (map->prec == -1 || check == 0))
	{
		ft_putchar_flags(s[i], fd, map, 0);
		i++;
	}
	if (check == 0)
		return ;
	while (s[i] && map->prec > 0)
	{
		ft_putchar_flags(s[i], fd, map, 0);
		i++;
		map->prec--;
	}
	while (map->min == 1 && map->pad > 0)
	{
		ft_putchar_flags(' ', 1, map, 0);
		map->pad--;
	}
	return ;
}

void	ft_nbrprinter_flags(char *s, int fd, t_map *map)
{
	int	i;

	i = 0;
	if (s[i] == '-')
		i++;
	if (map->nb == 0 && map->prec == 0)
	{
		if (map->plus == 1)
			ft_putchar_flags('+', fd, map, 0);
		else if (map->width == 0)
			return ;
		return ;
	}
	while (s[i])
	{
		ft_putchar_flags(s[i], fd, map, 0);
		i++;
	}
}

void	ft_putsign_fd(int fd, t_map *map)
{
	if (map->nb == 0 && map->plus == 1 && map->prec == 0)
	{
		return ;
	}
	if (map->typ == 'd' || map->typ == 'i' || map->typ == 'f')
	{
		if (map->nb < 0)
		{
			ft_putchar_flags('-', fd, map, 0);
		}
		if (map->nb >= 0 && map->plus == 1)
		{
			ft_putchar_flags('+', fd, map, 0);
			map->plus = 0;
		}
	}
}
