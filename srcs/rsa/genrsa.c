/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   genrsa.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 11:52:38 by mguerrea          #+#    #+#             */
/*   Updated: 2020/12/11 18:09:45 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"
#include <stdio.h>
#include "base64.h"

void format_key(t_rsa_priv key)
{
    int size;
    unsigned char buff[3072];
    int i;

    size = 3;
    size += asn1_size_int(key.n) + 2;
    size += asn1_size_int(key.e) + 2;
    size += asn1_size_int(key.p) + 2;
    size += asn1_size_int(key.q) + 2;
    buff[0] = 0x30;
    buff[1] = size;
    asn1_encode_int(&(buff[2]), 0);
    i = 5;
    asn1_encode_int(&(buff[i]), key.n);
    i += asn1_size_int(key.n) + 2;
    asn1_encode_int(&(buff[i]), key.e);
    i += asn1_size_int(key.e) + 2;
    asn1_encode_int(&(buff[i]), key.p);
    i += asn1_size_int(key.p) + 2;
    asn1_encode_int(&(buff[i]), key.q);
    i += asn1_size_int(key.q) + 2;
    for (int j = 0; j < size + 2; j++)
        ft_printf("%x ", buff[j]);
    ft_printf("\n");
    b64_encode(buff, size + 2, 1);
    ft_printf("\n");
}

void genkey(int size)
{
    t_rsa_priv key;

    ft_printf("Generating RSA private key, %d bit long modulus\n", size);
    key.p = get_prime(size / 2);
    ft_printf("\n");
    key.q = get_prime(size / 2);
    ft_printf("\n");
    key.n = key.p*key.q;
    key.e = 65537;
    ft_printf("p = %lu\nq = %lu\nn = %llu\n", key.p, key.q, key.n);
    format_key(key);
}

int ft_genrsa(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    genkey(64);
    return (0);
}