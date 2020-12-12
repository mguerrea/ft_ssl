/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 12:51:54 by mguerrea          #+#    #+#             */
/*   Updated: 2020/12/12 17:30:38 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

extern const t_conv g_tab_conv[];

int	parse_formating(char **format, va_list ap, int fd)
{
	t_options	options;
	int			type;
	const char	*flags = "#-+ 0";

	init_formating(&options, &type, fd);
	while (**format)
	{
		if (ft_strchr(flags, **format))
			get_flag(&options, flags, **format);
		else if (**format == '.')
			options.precision = 0;
		else if (ft_isdigit(**format))
			parse_digits(&options, *format);
		else if (**format == 'h' || **format == 'l' || **format == 'L')
			type += **format;
		else if (ft_strchr("diouxXfcsp%", **format))
			return (g_tab_conv[find_conv_function(conv(&options, type,
				*(*format)++))].function(ap, options));
		else
			return (0);
		(*format)++;
	}
	return (0);
}

int	parsing(char *format, va_list ap, int fd)
{
	int			count;

	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			count += parse_formating(&format, ap, fd);
		}
		else
		{
			ft_putchar_fd(*format, fd);
			count++;
			format++;
		}
	}
	va_end(ap);
	return (count);
}

int	ft_printf(char *format, ...)
{
	va_list		ap;

	va_start(ap, format);
	return (parsing(format, ap, 1));
}
