/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asn1_encode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 17:11:26 by mguerrea          #+#    #+#             */
/*   Updated: 2020/12/13 17:03:14 by mguerrea         ###   ########.fr       */
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

int asn1_size_privkey(t_rsa_priv key)
{
    int size;

    size = 3;
    size += asn1_size_int(key.n) + 2;
    size += asn1_size_int(key.e) + 2;
    size += asn1_size_int(key.d) + 2;
    size += asn1_size_int(key.p) + 2;
    size += asn1_size_int(key.q) + 2;
    size += asn1_size_int(key.dp) + 2;
    size += asn1_size_int(key.dq) + 2;
    size += asn1_size_int(key.qinv) + 2;
    return (size);
}

void asn1_encode_privkey(t_rsa_priv key, unsigned char *buff, int size)
{
    int i;

    buff[0] = 0x30;
    buff[1] = size;
    asn1_encode_int(&(buff[2]), 0);
    i = 5;
    asn1_encode_int(&(buff[i]), key.n);
    i += asn1_size_int(key.n) + 2;
    asn1_encode_int(&(buff[i]), key.e);
    i += asn1_size_int(key.e) + 2;
    asn1_encode_int(&(buff[i]), key.d);
    i += asn1_size_int(key.d) + 2;
    asn1_encode_int(&(buff[i]), key.p);
    i += asn1_size_int(key.p) + 2;
    asn1_encode_int(&(buff[i]), key.q);
    i += asn1_size_int(key.q) + 2;
    asn1_encode_int(&(buff[i]), key.dp);
    i += asn1_size_int(key.dp) + 2;
    asn1_encode_int(&(buff[i]), key.dq);
    i += asn1_size_int(key.dq) + 2;
    asn1_encode_int(&(buff[i]), key.qinv);
    i += asn1_size_int(key.qinv) + 2;
}

void asn1_encode_pubkey(t_rsa_priv key, unsigned char *buff, int size)
{
    int i;
    const unsigned char oid[] = {0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 
        0x0d, 0x01, 0x01, 0x01, 0x05, 0x00};

    buff[0] = 0x30;
    buff[1] = size + 20;
    i = 1;
    while (++i < 15 + 2)
        buff[i] = oid[i - 2];
    buff[17] = 3;
    buff[18] = size + 3;
    buff[19] = 0;
    buff[20] = 0x30;
    buff[21] = size;
    asn1_encode_int(&(buff[22]), key.n);
    i = 22 + asn1_size_int(key.n) + 2;
    asn1_encode_int(&(buff[i]), key.e);
}