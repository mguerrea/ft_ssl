/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 17:32:43 by mguerrea          #+#    #+#             */
/*   Updated: 2020/12/12 17:33:29 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_dprintf(int fd, char *format, ...)
{
	va_list		ap;

	va_start(ap, format);
	return (parsing(format, ap, fd));
}
