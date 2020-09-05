/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 15:23:40 by gmichaud          #+#    #+#             */
/*   Updated: 2018/12/30 19:53:06 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		conv_double(va_list ap, t_options options)
{
	char	*conv;
	int		ret;

	conv = NULL;
	if (!(conv = ft_dtoa(va_arg(ap, double), options)))
		return (-1);
	ret = print(conv, options);
	free(conv);
	return (ret);
}

int		conv_longdouble(va_list ap, t_options options)
{
	char	*conv;
	int		ret;

	conv = NULL;
	if (!(conv = ft_ldtoa(va_arg(ap, long double), options)))
		return (-1);
	ret = print(conv, options);
	free(conv);
	return (ret);
}

int		conv_string(va_list ap, t_options options)
{
	char	*arg;
	char	*conv;
	int		ret;

	arg = va_arg(ap, char*);
	if (!arg)
		conv = ft_strdup("(null)");
	else
		conv = ft_strdup(arg);
	if ((int)ft_strlen(conv) > options.precision && options.precision != -1)
		conv[options.precision] = 0;
	ret = print(conv, options);
	free(conv);
	return (ret);
}

int		conv_char(va_list ap, t_options options)
{
	return (printchar((char)va_arg(ap, int), options));
}

int		print_percent(va_list ap, t_options options)
{
	(void)ap;
	return (printchar('%', options));
}
