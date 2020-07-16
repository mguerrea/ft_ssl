/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 23:39:26 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/17 00:21:51 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64.h"

extern const char *g_base;

void b64_decode(unsigned char *str, unsigned int len, int fd)
{
    uint32_t nb;
    char chunk[4];
    unsigned int i;

    i = -1;
    while (++i < len - 3)
    {
        if(ft_isspace(str[i]))
            continue ;
        chunk[0] = ft_strchr(g_base, str[i]) - g_base;
        chunk[1] = ft_strchr(g_base, str[i + 1]) - g_base;
        chunk[2] = ft_strchr(g_base, str[i + 2]) - g_base;
        chunk[3] = ft_strchr(g_base, str[i + 3]) - g_base;
        nb = (uint32_t)chunk[0] << 18 | (uint32_t)chunk[1] << 12
            | (uint32_t)chunk[2] << 6 | (uint32_t)chunk[3];
        for (int j = 0; j < 3; j++)
            ft_putchar_fd((nb >> (8 * (2 - j))) & 0xff, fd);
        i += 4;
    }
}