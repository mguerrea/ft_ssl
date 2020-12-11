/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randint.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 12:24:37 by mguerrea          #+#    #+#             */
/*   Updated: 2020/12/11 14:34:27 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"

uint64_t randint64(uint64_t min, uint64_t max)
{
    int fd;
    char str[8];
    uint64_t nb;
    int i;

	if ((fd = open("/dev/urandom", O_RDONLY)) < 0)
		return (0);
    int ret;
    if ((ret = read(fd, str, 8)) < 8)
        return (0);
    nb = str[0];
    i = 0;
    while (++i < 8)
        nb = (nb << 8) | str[i];
	close(fd);
    nb = nb % (max - min) + min;
    return (nb);
}