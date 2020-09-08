/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 15:23:06 by gmichaud          #+#    #+#             */
/*   Updated: 2018/12/31 15:25:00 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		conv_uint(va_list ap, t_options options)
{
	char			*conv;
	unsigned int	nb;
	int				ret;

	nb = va_arg(ap, unsigned int);
	conv = NULL;
	if (!(conv = ft_ulltoa_form((unsigned long long)nb,
		options)))
		return (-1);
	if (!nb && !options.precision)
		ret = print("", options);
	else
		ret = print(conv, options);
	free(conv);
	return (ret);
}

int		conv_ulong(va_list ap, t_options options)
{
	char			*conv;
	unsigned long	nb;
	int				ret;

	nb = va_arg(ap, unsigned long);
	conv = NULL;
	if (!(conv = ft_ulltoa_form((unsigned long long)nb, options)))
		return (-1);
	if (!nb && !options.precision)
		ret = print("", options);
	else
		ret = print(conv, options);
	free(conv);
	return (ret);
}

int		conv_ulonglong(va_list ap, t_options options)
{
	char				*conv;
	unsigned long long	nb;
	int					ret;

	nb = va_arg(ap, unsigned long long);
	conv = NULL;
	if (!(conv = ft_ulltoa_form(nb, options)))
		return (-1);
	if (!nb && !options.precision)
		ret = print("", options);
	else
		ret = print(conv, options);
	free(conv);
	return (ret);
}

int		conv_ushort(va_list ap, t_options options)
{
	char			*conv;
	unsigned short	nb;
	int				ret;

	nb = (unsigned short)va_arg(ap, int);
	conv = NULL;
	if (!(conv = ft_ulltoa_form((unsigned long long)nb, options)))
		return (-1);
	if (!nb && !options.precision)
		ret = print("", options);
	else
		ret = print(conv, options);
	free(conv);
	return (ret);
}

int		conv_uchar(va_list ap, t_options options)
{
	char			*conv;
	unsigned char	nb;
	int				ret;

	nb = (unsigned char)va_arg(ap, int);
	conv = NULL;
	if (!(conv = ft_ulltoa_form((unsigned long long)nb, options)))
		return (-1);
	if (!nb && !options.precision)
		ret = print("", options);
	else
		ret = print(conv, options);
	free(conv);
	return (ret);
}
