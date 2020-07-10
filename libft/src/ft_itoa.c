/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 14:41:47 by mguerrea          #+#    #+#             */
/*   Updated: 2018/11/05 14:42:31 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_stradd(char *str, char value)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	str[i] = value;
	str[i + 1] = '\0';
}

static void		recursif(long nb, char *str)
{
	if (nb >= 10)
	{
		recursif(nb / 10, str);
		recursif(nb % 10, str);
	}
	else
		ft_stradd(str, nb + '0');
}

char			*ft_itoa(int nb)
{
	char	*str;
	int		value;
	int		i;
	long	lng;

	i = 0;
	value = nb;
	lng = (long)nb;
	while (value != 0)
	{
		value = value / 10;
		i++;
	}
	if (!(str = ft_strnew(i + 1)))
		return (NULL);
	if (lng < 0)
	{
		str[0] = '-';
		lng = -lng;
	}
	recursif(lng, str);
	return (str);
}
