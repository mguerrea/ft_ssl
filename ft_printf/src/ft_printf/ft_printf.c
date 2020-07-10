/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 12:51:54 by mguerrea          #+#    #+#             */
/*   Updated: 2018/12/31 17:15:27 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	parse_formating(char **format, va_list ap,
		int *tab_type, t_print_fct *print)
{
	t_options	options;
	int			type;
	const char	*flags = "#-+ 0";

	init_formating(&options, &type);
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
			return (print[find_conv_function(conv(&options, type, *(*format)++),
				tab_type)](ap, options));
		else
			return (0);
		(*format)++;
	}
	return (0);
}

int	parsing(char *format, va_list ap, int *tab_type, t_print_fct *print)
{
	int			count;

	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			count += parse_formating(&format, ap, tab_type, print);
		}
		else
		{
			ft_putchar(*format);
			count++;
			format++;
		}
	}
	va_end(ap);
	return (count);
}

int	ft_printf(char *format, ...)
{
	t_print_fct	print[NBTYPES];
	int			tab_type[NBTYPES];
	va_list		ap;

	va_start(ap, format);
	fill_print(print);
	fill_type(tab_type);
	return (parsing(format, ap, tab_type, print));
}
