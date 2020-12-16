/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printkey.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 16:30:29 by mguerrea          #+#    #+#             */
/*   Updated: 2020/12/16 18:34:15 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"

void format_privkey(t_rsa_priv key, t_rsa_opt opt)
{
    int size;
    unsigned char buff[3072];

    size = asn1_size_privkey(key);
    asn1_encode_privkey(key, buff, size);
    if (opt.des && opt.format[1] == PEM)
        encrypt_key(opt, buff, size + 2);
    else if (opt.format[1] == PEM)
    {
        ft_putstr_fd(PRIV_B, opt.fd[1]);
        b64_encode(buff, size + 2, opt.fd[1]);
        ft_putchar_fd('\n', opt.fd[1]);
        ft_putstr_fd(PRIV_E, opt.fd[1]);
    }
    else
        write(opt.fd[1], buff, size + 2);
    ft_memset(&key, 0, sizeof(t_rsa_priv));
}

void format_pubkey(t_rsa_priv key, t_rsa_opt opt)
{
    int size;
    unsigned char buff[3072];

    size = asn1_size_int(key.n) + asn1_size_int(key.e) + 4;
    asn1_encode_pubkey(key, buff, size);
    if (opt.format[1] == PEM)
    {
        ft_putstr_fd(PUB_B, opt.fd[1]);
        b64_encode(buff, size + 2 + 20, opt.fd[1]);
        ft_putchar_fd('\n', opt.fd[1]);
        ft_putstr_fd(PUB_E, opt.fd[1]);
    }
    else
        write(opt.fd[1], buff, size + 22);
    ft_memset(&key, 0, sizeof(t_rsa_priv));
}

void print_infos(t_rsa_opt opt, t_rsa_priv key)
{
    if (opt.pubin == 0)
    {
        ft_dprintf(opt.fd[1], "RSA Private-Key: (64 bit, 2 primes)\n");
        ft_dprintf(opt.fd[1], "modulus: %lu (0x%lx)\n", key.n, key.n);
        ft_dprintf(opt.fd[1], "publicExponent: %lu (0x%lx)\n", key.e, key.e);
        ft_dprintf(opt.fd[1], "privateExponent: %lu (0x%lx)\n", key.d, key.d);
        ft_dprintf(opt.fd[1], "prime1: %lu (0x%lx)\n", key.p, key.p);
        ft_dprintf(opt.fd[1], "prime2: %lu (0x%lx)\n", key.q, key.q);
        ft_dprintf(opt.fd[1], "exponent1: %lu (0x%lx)\n", key.dp, key.dp);
        ft_dprintf(opt.fd[1], "exponent2: %lu (0x%lx)\n", key.dq, key.dq);
        ft_dprintf(opt.fd[1], "coefficient: %lu (0x%lx)\n", key.qinv, key.qinv);
    }
    else
    {
        ft_dprintf(opt.fd[1], "RSA Public-Key: (64 bit)\n");
        ft_dprintf(opt.fd[1], "Modulus: %lu (0x%lx)\n", key.n, key.n);
        ft_dprintf(opt.fd[1], "Exponent: %lu (0x%lx)\n", key.e, key.e);
    }
}