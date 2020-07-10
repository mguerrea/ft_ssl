/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_double_conv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 09:26:00 by gmichaud          #+#    #+#             */
/*   Updated: 2018/12/31 14:33:26 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static long long	ft_round(long long n)
{
	int	unit;

	unit = (int)(n % 10);
	if (unit >= 5)
		n += 10;
	return (n / 10);
}

static char			*get_decimal(long double f, long long n, int prec)
{
	long long	d;
	int			len;
	int			i;
	char		*s1;
	char		*s2;

	prec = (prec == -1) ? 6 : prec;
	d = ft_llabs((long long)((f - (double)n) * ft_pow(10, prec + 1)));
	d = ft_round(d);
	if (!(s1 = ft_strnew(sizeof(*s1) * prec)))
		return (NULL);
	len = ft_nbrlen(d);
	i = 0;
	while (i < prec - len)
		s1[i++] = '0';
	s2 = ft_lltoa(d);
	ft_strcat(s1, s2);
	free(s2);
	return (s1);
}

static char			*get_formatted_string(long double f, t_options options)
{
	char	*s;
	int		len;
	int		sign;

	sign = 0;
	len = ft_nbrlen((long long)f);
	len += options.precision;
	if ((options.flags & (SIGN | SPACE)) || f < 0)
		sign = 1;
	if (!(s = ft_strnew(sizeof(char) * (len + sign + 1))))
		return (NULL);
	if (f < 0)
		s[0] = '-';
	else if (options.flags & SIGN)
		s[0] = '+';
	else if (options.flags & SPACE)
		s[0] = ' ';
	return (s);
}

static char			*join_parts(long double f, t_options options,
						char *part1, char *part2)
{
	char	*dest;
	char	*padding;

	padding = NULL;
	if (!(dest = get_formatted_string(f, options)))
		return (NULL);
	ft_strcat(dest, part1);
	if (options.precision != 0 || options.flags & ALT)
		ft_strcat(dest, ".");
	if (part2)
		ft_strcat(dest, part2);
	ft_strdel(&part1);
	if (options.precision != 0)
		ft_strdel(&part2);
	if (options.field_size > ft_strlen(dest) && options.flags & ZERO)
	{
		if (!(padding = ft_strnew(options.field_size - ft_strlen(dest))))
			return (NULL);
		ft_memset(padding, '0', options.field_size - ft_strlen(dest));
	}
	return ((padding) ? ft_strjoin(padding, dest) : dest);
}

char				*ft_ldtoa(long double f, t_options options)
{
	long long	n;
	char		*part1;
	char		*part2;

	part2 = NULL;
	n = (long long)f;
	if (!(part1 = ft_lltoa(ft_llabs(n))))
		return (NULL);
	if (options.precision != 0)
		if (!(part2 = get_decimal(f, n, options.precision)))
			return (NULL);
	return (join_parts(f, options, part1, part2));
}
