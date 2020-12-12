/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   genrsa.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 11:52:38 by mguerrea          #+#    #+#             */
/*   Updated: 2020/12/12 12:58:24 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"
#include <stdio.h>
#include "base64.h"

void format_key(t_rsa_priv key, int fd)
{
    int size;
    unsigned char buff[3072];

    size = asn1_size_privkey(key);
    asn1_encode_privkey(key, buff, size);
    // for (int j = 0; j < size + 2; j++)
    //     ft_printf("%x ", buff[j]);
    // ft_printf("\n");
    ft_printf("e is %lu (0x0%0x)\n", key.e, key.e);
    ft_putstr_fd("-----BEGIN RSA PRIVATE KEY-----\n", fd);
    b64_encode(buff, size + 2, fd);
    ft_putchar_fd('\n', fd);
    ft_putstr_fd("-----END RSA PRIVATE KEY-----\n", fd);
}

void genkey(int size, int fd)
{
    t_rsa_priv key;

    ft_printf("Generating RSA private key, %d bit long modulus\n", size);
    key.p = get_prime(size / 2);
    ft_printf("\n");
    key.q = get_prime(size / 2);
    ft_printf("\n");
    key.n = key.p*key.q;
    key.e = 65537;
    key.d = inv_mod(key.e, (key.p - 1)*(key.q - 1));
    key.dp = key.d % (key.p - 1);
    key.dq = key.d % (key.q - 1);
    key.qinv = inv_mod(key.q, key.p);
    // ft_printf("p = %lu\nq = %lu\nn = %llu\nd = %lu\n", key.p, key.q, key.n, key.d);
    format_key(key, fd);
}

int ft_genrsa(int argc, char **argv)
{
    int fd;
    (void)argc;
    (void)argv;

    if (argv[1] && ft_strcmp(argv[1], "-o") == 0 && argv[2])
        fd = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY);
    else
        fd = 1;
    genkey(64, fd);
    return (0);
}