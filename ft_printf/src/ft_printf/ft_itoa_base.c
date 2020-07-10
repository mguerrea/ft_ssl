/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 14:41:47 by mguerrea          #+#    #+#             */
/*   Updated: 2018/12/31 17:09:27 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static void		ft_stradd(char *str, int value, const char *map)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	str[i] = map[value];
	str[i + 1] = '\0';
}

static void		recursif(unsigned long long nb, char *str,
						int base, const char *map)
{
	if (nb >= (unsigned long long)base)
	{
		recursif(nb / base, str, base, map);
		recursif(nb % base, str, base, map);
	}
	else
		ft_stradd(str, nb, map);
}

static int		ft_nbrlen_base(unsigned long long nb, int base)
{
	int i;

	if (nb == 0)
		return (1);
	i = 0;
	while (nb != 0)
	{
		nb = nb / base;
		i++;
	}
	return (i);
}

static void		padding(int len, char *str)
{
	int i;

	i = 0;
	while (i < len)
		str[i++] = '0';
}

char			*ft_lltoa_base(unsigned long long nb, int base,
					char type, t_options options)
{
	char		*str;
	int			i;
	const char	*map_min = "0123456789abcdef";
	const char	*map_maj = "0123456789ABCDEF";

	if (!(str = ft_strnew(ft_max(ft_max(ft_nbrlen_base(nb, base),
			options.field_size), options.precision) + 2)))
		return (NULL);
	i = 0;
	if (options.precision > (int)options.field_size
		|| (options.flags & ZERO && (!(options.flags & PADD_RIGHT))))
		padding(ft_max(options.field_size - i, options.precision)
			- ft_nbrlen_base(nb, base), &str[i]);
	else if (options.flags & PADD_RIGHT
		|| options.precision <= (int)options.field_size)
		padding(options.precision - ft_nbrlen_base(nb, base), &str[i]);
	recursif(nb, str, base, (type == 'x') ? map_min : map_maj);
	return (str);
}
