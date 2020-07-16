/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 12:19:24 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/16 12:25:31 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64.h"

extern const char *g_base;

void    convert_chunk(char chunk[4], uint32_t nb, int len)
{
    int i;

    i = 0;
    while (i < len)
    {
        chunk[i] = g_base[(nb >> (6 * (len - i - 1))) & 0b111111];
        i++;
    }
    while (i < 4)
    {
        chunk[i] = '=';
        i++;
    }
}

void b64_padding(char *str, unsigned int len)
{
    uint32_t nb;
    char chunk[4];

    if (len == 0)
        return ;
    if (len == 1)
        nb = (uint32_t)str[0] << 4;
    else
        nb = (uint32_t)str[0] << 10 | (uint32_t)str[1] << 2;
    convert_chunk(chunk, nb, len + 1);
    for (int j = 0; j < 4; j++)
        ft_printf("%c", chunk[j]);
}

void    b64_encode(char *str, unsigned int len)
{
    uint32_t nb;
    char chunk[4];
    unsigned int i;

    i = 0;
    while (i < len - 2)
    {
        nb = (uint32_t)str[i] << 16 | (uint32_t)str[i + 1] << 8
            | (uint32_t)str[i + 2];
        convert_chunk(chunk, nb, 4);
        for (int j = 0; j < 4; j++)
            ft_printf("%c", chunk[j]);
        i+=3;
    }
    b64_padding(&(str[i]), len - i);
    ft_printf("\n");
}