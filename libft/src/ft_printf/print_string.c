/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 18:40:29 by gmichaud          #+#    #+#             */
/*   Updated: 2020/12/12 17:18:13 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_padding(int len, char c, int fd)
{
	while (len--)
		ft_putchar_fd(c, fd);
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
			ft_putchar_fd(*(s++), options.fd);
		print_padding(options.field_size - len, fill, options.fd);
	}
	ft_putstr_fd(s, options.fd);
	if (options.field_size > len && options.flags & PADD_RIGHT)
		print_padding(options.field_size - len, ' ', options.fd);
	return ((len > options.field_size) ? len : options.field_size);
}

int		printchar(char c, t_options options)
{
	char	fill;

	fill = (options.flags & ZERO) ? '0' : ' ';
	if (options.field_size > 1 && !(options.flags & PADD_RIGHT))
		print_padding(options.field_size - 1, fill, options.fd);
	write(options.fd, &c, 1);
	if (options.field_size > 1 && options.flags & PADD_RIGHT)
		print_padding(options.field_size - 1, ' ', options.fd);
	return ((1 > options.field_size) ? 1 : options.field_size);
}
