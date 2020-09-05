/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 15:26:32 by gmichaud          #+#    #+#             */
/*   Updated: 2018/12/31 16:52:20 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		conv_oct(va_list ap, t_options options)
{
	char			*conv;
	int				ret;
	unsigned int	nb;

	ret = 0;
	nb = va_arg(ap, unsigned int);
	if (!(conv = ft_lltoa_base((unsigned long long)nb, 8, 'x', options)))
		return (-1);
	if (options.precision == 0 && !(options.flags & ALT) && nb == 0)
		conv[0] = '\0';
	if (options.flags & ALT && nb != 0)
	{
		if ((options.flags & ZERO) == 0 || options.flags & PADD_RIGHT)
			ft_endcpy(&conv[1], conv, ft_strlen(conv) - 1);
		conv[0] = '0';
	}
	ret += print(conv, options);
	free(conv);
	return (ret);
}

int		conv_loct(va_list ap, t_options options)
{
	char			*conv;
	int				ret;
	unsigned long	nb;

	ret = 0;
	nb = va_arg(ap, unsigned long);
	if (!(conv = ft_lltoa_base((unsigned long long)nb, 8, 'x', options)))
		return (-1);
	if (options.precision == 0 && !(options.flags & ALT) && nb == 0)
		conv[0] = '\0';
	if (options.flags & ALT && nb != 0)
	{
		if ((options.flags & ZERO) == 0 || options.flags & PADD_RIGHT)
			ft_endcpy(&conv[1], conv, ft_strlen(conv) - 1);
		conv[0] = '0';
	}
	ret += print(conv, options);
	free(conv);
	return (ret);
}

int		conv_lloct(va_list ap, t_options options)
{
	char			*conv;
	int				ret;
	unsigned long	nb;

	ret = 0;
	nb = va_arg(ap, unsigned long long);
	if (!(conv = ft_lltoa_base(nb, 8, 'x', options)))
		return (-1);
	if (options.precision == 0 && !(options.flags & ALT) && nb == 0)
		conv[0] = '\0';
	if (options.flags & ALT && nb != 0)
	{
		if ((options.flags & ZERO) == 0 || options.flags & PADD_RIGHT)
			ft_endcpy(&conv[1], conv, ft_strlen(conv) - 1);
		conv[0] = '0';
	}
	ret += print(conv, options);
	free(conv);
	return (ret);
}

int		conv_hoct(va_list ap, t_options options)
{
	char			*conv;
	int				ret;
	unsigned int	nb;

	ret = 0;
	nb = (unsigned short)va_arg(ap, unsigned int);
	if (!(conv = ft_lltoa_base((unsigned long long)nb, 8, 'x', options)))
		return (-1);
	if (options.precision == 0 && !(options.flags & ALT) && nb == 0)
		conv[0] = '\0';
	if (options.flags & ALT && nb != 0)
	{
		if ((options.flags & ZERO) == 0 || options.flags & PADD_RIGHT)
			ft_endcpy(&conv[1], conv, ft_strlen(conv) - 1);
		conv[0] = '0';
	}
	ret += print(conv, options);
	free(conv);
	return (ret);
}

int		conv_hhoct(va_list ap, t_options options)
{
	char			*conv;
	int				ret;
	unsigned int	nb;

	ret = 0;
	nb = (unsigned char)va_arg(ap, unsigned int);
	if (!(conv = ft_lltoa_base((unsigned long long)nb, 8, 'x', options)))
		return (-1);
	if (options.precision == 0 && !(options.flags & ALT) && nb == 0)
		conv[0] = '\0';
	if (options.flags & ALT && nb != 0)
	{
		if ((options.flags & ZERO) == 0 || options.flags & PADD_RIGHT)
			ft_endcpy(&conv[1], conv, ft_strlen(conv) - 1);
		conv[0] = '0';
	}
	ret += print(conv, options);
	free(conv);
	return (ret);
}
