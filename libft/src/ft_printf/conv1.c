/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 18:40:47 by gmichaud          #+#    #+#             */
/*   Updated: 2018/12/31 13:34:42 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		conv_int(va_list ap, t_options options)
{
	char	*conv;
	int		nb;
	int		ret;

	conv = NULL;
	nb = va_arg(ap, int);
	if (!(conv = ft_lltoa_form((long long)nb, options)))
		return (-1);
	if (!nb && !options.precision)
		ret = print("", options);
	else
		ret = print(conv, options);
	free(conv);
	return (ret);
}

int		conv_long(va_list ap, t_options options)
{
	char	*conv;
	long	nb;
	int		ret;

	conv = NULL;
	nb = va_arg(ap, long);
	if (!(conv = ft_lltoa_form((long long)nb, options)))
		return (-1);
	if (!nb && !options.precision)
		ret = print("", options);
	else
		ret = print(conv, options);
	free(conv);
	return (ret);
}

int		conv_longlong(va_list ap, t_options options)
{
	char		*conv;
	long long	nb;
	int			ret;

	conv = NULL;
	nb = va_arg(ap, long long);
	if (!(conv = ft_lltoa_form(nb, options)))
		return (-1);
	if (!nb && !options.precision)
		ret = print("", options);
	else
		ret = print(conv, options);
	free(conv);
	return (ret);
}

int		conv_short(va_list ap, t_options options)
{
	char	*conv;
	short	nb;
	int		ret;

	nb = (short)va_arg(ap, int);
	conv = NULL;
	if (!(conv = ft_lltoa_form((long long)nb, options)))
		return (-1);
	if (!nb && !options.precision)
		ret = print("", options);
	else
		ret = print(conv, options);
	free(conv);
	return (ret);
}

int		conv_charnb(va_list ap, t_options options)
{
	char	*conv;
	char	nb;
	int		ret;

	nb = (short)va_arg(ap, int);
	conv = NULL;
	if (!(conv = ft_lltoa_form((long long)nb, options)))
		return (-1);
	if (!nb && !options.precision)
		ret = print("", options);
	else
		ret = print(conv, options);
	free(conv);
	return (ret);
}
