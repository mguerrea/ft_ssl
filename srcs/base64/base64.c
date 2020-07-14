/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 19:37:25 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/14 20:02:23 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "ft_printf.h"

const char *g_base = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void    convert_chunk(char chunk[4], uint32_t nb)
{
    chunk[0] = g_base[(nb >> 18) & 0b111111];
    chunk[1] = g_base[(nb >> 12) & 0b111111];
    chunk[2] = g_base[(nb >> 6) & 0b111111];
    chunk[3] = g_base[nb & 0b111111];
}

void    base64_string(char *str)
{
    uint32_t nb;
    char chunk[4];
    int i;

    i = 0;
    while (str[i] && str[i+1] && str[i+2])
    {
        nb = (uint32_t)str[i] << 16 | (uint32_t)str[i + 1] << 8
            | (uint32_t)str[i + 2];
        convert_chunk(chunk, nb);
        for (int j = 0; j < 4; j++)
            ft_printf("%c", chunk[j]);
        i+=3;
    }
    ft_printf("\n");
}

int		ft_base64(int argc, char **argv)
{
    (void)argc;
    base64_string(argv[1]);
    return(0);
}