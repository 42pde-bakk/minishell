/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_moreputstuff.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/04 19:24:51 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/06/09 17:35:00 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_apostrophe(char *s, t_map *map)
{
	char	*ret;
	int		i;
	int		n;

	i = 0;
	n = 0;
	if (map->apos <= -1 || map->typ == 'x' || map->typ == 'X')
		return (s);
	ret = ft_calloc(ft_strlen_peer(s) + map->apos + 1, sizeof(char));
	if (!ret)
		return (0);
	while (s[n])
	{
		ret[i] = s[n];
		i++;
		n++;
		if ((ft_strlen_peer(s) - n) % 3 == 0 && map->apos > 0)
		{
			ret[i] = ',';
			i++;
			map->apos--;
		}
	}
	free(s);
	return (ret);
}

void	ft_put0x(int fd, t_map *map)
{
	if (map->nb == 0 && map->prec == 0 && map->hash == 1 && map->typ == 'o')
		ft_putchar_flags('0', fd, map, 0);
	if (map->bon != 5 && (map->typ == 'p' || map->typ == 'a' || map->typ == 'A'
	|| (map->hash == 1 && map->nb != 0 && (map->typ == 'x' || map->typ == 'X'
	|| map->typ == 'o'))))
	{
		ft_putchar_flags('0', fd, map, 0);
		if (map->min == 1)
		{
			if (map->typ == 'o')
				map->pfill--;
			else
				map->pad--;
		}
		if (map->typ == 'x' || map->typ == 'p' || map->typ == 'X'
	|| map->typ == 'A' || map->typ == 'a')
		{
			if (map->typ == 'X' || map->typ == 'A')
				ft_putchar_flags('X', fd, map, 0);
			else
				ft_putchar_flags('x', fd, map, 0);
			if (map->min == 1)
				map->pad--;
		}
	}
}

void	ft_nbrflagger_flags(char *s, int fd, t_map *map)
{
	if ((map->plus == 1 && map->nb >= 0) || map->nb < 0)
		map->pad--;
	if (map->zero == 1 && map->pad > 0 && map->prec > -1)
		map->zero = 0;
	if (map->spac == 1 && map->plus == 0 && map->hash == 0 && map->nb >= 0)
	{
		ft_putchar_flags(' ', fd, map, 0);
		map->pad--;
	}
	if (map->nb == 0 && map->prec == 0 && map->width > 1)
		map->pad++;
	if (map->prec == -1 && map->typ == 'o' && map->hash == 1 && map->nb != 0)
		map->pad--;
	if (map->prec < ft_strlen_peer(s) && map->prec != -1 && map->typ == 'o'
	&& map->hash == 1)
		map->pad--;
	if (map->hash == 1 && map->nb != 0 && map->min == 0)
	{
		if (map->typ == 'o')
			map->pfill--;
		if (map->typ == 'x' || map->typ == 'X')
			map->pad = map->pad - 2;
	}
}

void	ft_lastputstuff(char *s, int fd, t_map *map)
{
	while (map->pfill > 0)
	{
		ft_putchar_flags('0', fd, map, 0);
		map->pfill--;
	}
	ft_nbrprinter_flags(s, fd, map);
	while (map->min == 1 && map->pad > 0)
	{
		ft_putchar_flags(' ', fd, map, 0);
		map->pad--;
	}
}

char	*ft_nbrputter_flags(char *s, int fd, t_map *map)
{
	s = ft_apostrophe(s, map);
	map->pfill = map->prec - ft_strlen_peer(s);
	if (map->width > ft_strlen_peer(s) && map->width > map->prec)
		map->pad = (map->prec > ft_strlen_peer(s)) ? map->width - map->prec
		: map->width - ft_strlen_peer(s);
	ft_nbrflagger_flags(s, fd, map);
	if (map->typ == 'p' && map->min == 0)
		map->pad = map->pad - 2;
	while (map->pad > 0 && map->min == 0 && map->zero == 0)
	{
		ft_putchar_flags(' ', fd, map, 0);
		map->pad--;
	}
	ft_putsign_fd(fd, map);
	ft_put0x(fd, map);
	while (map->zero == 1 && map->pad > 0)
	{
		ft_putchar_flags('0', fd, map, 0);
		map->pad--;
	}
	ft_lastputstuff(s, fd, map);
	return (s);
}
