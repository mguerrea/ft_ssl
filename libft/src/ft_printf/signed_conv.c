/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signed_conv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 13:12:47 by gmichaud          #+#    #+#             */
/*   Updated: 2018/12/31 14:35:56 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		get_formatted_string(char **s, long long n, t_options options)
{
	int		len;
	int		sign;

	sign = 0;
	len = ft_nbrlen(n);
	len = (options.precision > len) ? options.precision : len;
	if ((options.flags & (SIGN | SPACE)) || n < 0)
		sign = 1;
	if (!(*s = ft_strnew(len + sign)))
		return (-1);
	ft_memset(*s, '0', len + sign);
	if (n < 0)
		*s[0] = '-';
	else if (options.flags & SIGN)
		*s[0] = '+';
	else if (options.flags & SPACE)
		*s[0] = ' ';
	return (len + sign);
}

char			*ft_lltoa_form(long long n, t_options options)
{
	char	*s;
	int		len;

	if ((len = get_formatted_string(&s, n, options)) == -1)
		return (NULL);
	len -= 1;
	if (n == 0)
		s[len] = '0';
	while (n != 0)
	{
		if (n > 0)
			s[len] = n % 10 + 48;
		if (n < 0)
			s[len] = -(n % 10) + 48;
		n = n / 10;
		len--;
	}
	return (s);
}
