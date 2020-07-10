/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned_conv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 16:00:59 by gmichaud          #+#    #+#             */
/*   Updated: 2018/12/31 14:36:49 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_formatted_string(char **s,
	unsigned long long n, t_options options)
{
	int	len;

	len = ft_unbrlen(n);
	len = (options.precision > len) ? options.precision : len;
	if (!(*s = ft_strnew(len)))
		return (-1);
	ft_memset(*s, '0', len);
	return (len);
}

char		*ft_ulltoa_form(unsigned long long n, t_options options)
{
	char	*s;
	int		len;

	(void)options;
	if ((len = get_formatted_string(&s, n, options)) == -1)
		return (NULL);
	len -= 1;
	if (n == 0)
		s[len] = '0';
	while (n != 0)
	{
		if (n > 0)
			s[len] = n % 10 + 48;
		n = n / 10;
		len--;
	}
	return (s);
}
