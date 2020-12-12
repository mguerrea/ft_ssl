/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asn1_decode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 14:01:45 by mguerrea          #+#    #+#             */
/*   Updated: 2020/12/12 16:01:28 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"

int asn1_decode_int(unsigned char *buff, uint64_t *n)
{
    int size;
    int i;

    *n = 0;
    if((size = buff[1]) > 9 || (size == 9 && buff[2] != 0))
        return (-1);
    i = 1;
    while (++i < size + 2)
        *n = (*n << 8) | buff[i];
    return (0);
}

int asn1_decode_pubkey(t_rsa_priv *key, unsigned char *buff)
{
    (void)key;
    (void)buff;
    return (0);
}

int asn1_decode_privkey(t_rsa_priv *key, unsigned char *buff)
{
    int i;

    if (buff[0] != 0x30)
        return (ft_printf("invalid offset\n"));
    if (buff[1] >= 0x80)
        return (ft_printf("key too long, only 64 bits is supported\n"));
    i = 5;
    if (asn1_decode_int(&(buff[i]), &(key->n)) == -1)
        return (ft_printf("key too long, only 64 bits is supported\n"));
    i += buff[i + 1] + 2;
    asn1_decode_int(&(buff[i]), &(key->e));
    i += buff[i + 1] + 2;
    asn1_decode_int(&(buff[i]), &(key->d));
    i += buff[i + 1] + 2;
    asn1_decode_int(&(buff[i]), &(key->p));
    i += buff[i + 1] + 2;
    asn1_decode_int(&(buff[i]), &(key->q));
    i += buff[i + 1] + 2;
    asn1_decode_int(&(buff[i]), &(key->dp));
    i += buff[i + 1] + 2;
    asn1_decode_int(&(buff[i]), &(key->dq));
    i += buff[i + 1] + 2;
    asn1_decode_int(&(buff[i]), &(key->qinv));
    return (0);
}