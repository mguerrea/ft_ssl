/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printkey.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 16:30:29 by mguerrea          #+#    #+#             */
/*   Updated: 2020/12/12 16:37:42 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"

void format_privkey(t_rsa_priv key, int fd)
{
    int size;
    unsigned char buff[3072];

    size = asn1_size_privkey(key);
    asn1_encode_privkey(key, buff, size);
    ft_putstr_fd("-----BEGIN RSA PRIVATE KEY-----\n", fd);
    b64_encode(buff, size + 2, fd);
    ft_putchar_fd('\n', fd);
    ft_putstr_fd("-----END RSA PRIVATE KEY-----\n", fd);
    ft_memset(&key, 0, sizeof(t_rsa_priv));
}

void print_infos(t_rsa_opt opt, t_rsa_priv key)
{
    if (opt.pubin == 0)
    {
        ft_printf("RSA Private-Key: (64 bit, 2 primes)\n");
        ft_printf("modulus: %lu (0x%lx)\n", key.n, key.n);
        ft_printf("publicExponent: %lu (0x%lx)\n", key.e, key.e);
        ft_printf("privateExponent: %lu (0x%lx)\n", key.d, key.d);
        ft_printf("prime1: %lu (0x%lx)\n", key.p, key.p);
        ft_printf("prime2: %lu (0x%lx)\n", key.q, key.q);
        ft_printf("exponent1: %lu (0x%lx)\n", key.dp, key.dp);
        ft_printf("exponent2: %lu (0x%lx)\n", key.dq, key.dq);
        ft_printf("coefficient: %lu (0x%lx)\n", key.qinv, key.qinv);
    }
    else
    {
        ft_printf("RSA Public-Key: (64 bit)\n");
        ft_printf("Modulus: %lu (0x%lx)\n", key.n, key.n);
        ft_printf("Exponent: %lu (0x%lx)\n", key.e, key.e);
    }
    
}