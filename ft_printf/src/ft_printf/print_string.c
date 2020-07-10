/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 18:40:29 by gmichaud          #+#    #+#             */
/*   Updated: 2018/12/31 17:04:07 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_padding(int len, char c)
{
	while (len--)
		ft_putchar(c);
}

int		print(const char *s, t_options options)
{
	char	fill;
	size_t	len;

	len = ft_strlen(s);
	fill = (options.flags & ZERO && options.precision == -1) ? '0' : ' ';
	if (options.field_size > len && !(options.flags & PADD_RIGHT))
	{
		if ((s[0] == '-' || s[0] == '+' || s[0] == ' ') && fill == '0')
			ft_putchar(*(s++));
		print_padding(options.field_size - len, fill);
	}
	ft_putstr(s);
	if (options.field_size > len && options.flags & PADD_RIGHT)
		print_padding(options.field_size - len, ' ');
	return ((len > options.field_size) ? len : options.field_size);
}

int		printchar(char c, t_options options)
{
	char	fill;

	fill = (options.flags & ZERO) ? '0' : ' ';
	if (options.field_size > 1 && !(options.flags & PADD_RIGHT))
		print_padding(options.field_size - 1, fill);
	write(1, &c, 1);
	if (options.field_size > 1 && options.flags & PADD_RIGHT)
		print_padding(options.field_size - 1, ' ');
	return ((1 > options.field_size) ? 1 : options.field_size);
}
