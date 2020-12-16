/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   genrsa.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 11:52:38 by mguerrea          #+#    #+#             */
/*   Updated: 2020/12/16 15:50:00 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"
#include <stdio.h>
#include "base64.h"
#include "utils.h"

void genkey(int size, t_rsa_opt opt)
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
    ft_printf("e is %lu (0x0%0x)\n", key.e, key.e);
    format_privkey(key, opt);
}

int ft_genrsa(int argc, char **argv)
{
    t_rsa_opt opt;

    (void)argc;
    (void)argv;
    rsa_opt_init(&opt);
    if (argv[1] && ft_strcmp(argv[1], "-o") == 0 && argv[2])
        opt.fd[1] = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY);
    else
        opt.fd[1] = 1;
    if (opt.fd[1] == -1)
        return (error_file(argv[2], "genrsa"));
    genkey(64, opt);
    return (0);
}