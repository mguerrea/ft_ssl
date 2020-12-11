/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asn1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 17:11:26 by mguerrea          #+#    #+#             */
/*   Updated: 2020/12/11 18:03:04 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"

int asn1_size_int(uint64_t nb)
{
    int size;
    uint64_t tmp;
    
    size = 1;
    tmp = nb;
    while (tmp / 256)
    {
        tmp = tmp / 256;
        size++;
    }
    if (nb >> (size * 8 - 1))
        size++;
    return (size);
}

void asn1_encode_int(unsigned char *buff, uint64_t nb)
{
    int size;
    int i;

    size = asn1_size_int(nb);
    buff[0] = 2;
    buff[1] = size;
    i = 2;
    if (size == 9 || nb <= ((1L << (size - 1)*8) - 1))
    {
        buff[2] = 0;
        i++;
    }
    while (i - 2 < size)
    {
        buff[i] = (nb >> ((size - (i-1))*8));
        i++;
    }
}