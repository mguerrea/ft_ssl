/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 15:01:31 by gmichaud          #+#    #+#             */
/*   Updated: 2018/12/31 17:08:03 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		conv_pointer(va_list ap, t_options options)
{
	char				*conv;
	unsigned long long	nb;
	int					ret;

	nb = va_arg(ap, unsigned long long);
	ret = 0;
	if (!(conv = ft_lltoa_base(nb, 16, 'x', options)))
		return (-1);
	if (options.precision == 0)
		conv[0] = '\0';
	if ((options.flags & ZERO) == 0 || options.flags & PADD_RIGHT)
		ft_endcpy(&conv[2], conv, ft_strlen(conv) - 1);
	conv[0] = '0';
	conv[1] = 'x';
	ret += print(conv, options);
	free(conv);
	return (ret);
}

int		conv_none(va_list ap, t_options options)
{
	(void)ap;
	(void)options;
	return (0);
}
