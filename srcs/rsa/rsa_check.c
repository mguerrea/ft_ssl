/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 18:52:45 by mguerrea          #+#    #+#             */
/*   Updated: 2020/12/16 19:11:11 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"

void rsa_check(t_rsa_priv key, t_rsa_opt opt)
{
    int ok;

    ok = 0;
    if (miller_rabin64(key.p) != 1)
        ok += ft_dprintf(opt.fd[1], "RSA key error: p not prime\n");
    if (miller_rabin64(key.q) != 1)
        ok += ft_dprintf(opt.fd[1], "RSA key error: q not prime\n");
    if (key.n != key.q * key.p)
        ok += ft_dprintf(opt.fd[1], "RSA key error: n does not equal p q\n");
    if (inv_mod(key.e, (key.p - 1)*(key.q - 1)) != key.d)
        ok += ft_dprintf(opt.fd[1], "RSA key error: d e not congruent to 1\n");
    if (key.d % (key.p - 1) != key.dp)
        ok += ft_dprintf(opt.fd[1], "RSA key error: dmp1 not congruent to d\n");
    if (key.d % (key.q - 1) != key.dq)
        ok += ft_dprintf(opt.fd[1], "RSA key error: dmq1 not congruent to d\n");
    if (inv_mod(key.q, key.p) != key.qinv)
        ok += ft_dprintf(opt.fd[1], "RSA key error: iqmp not inverse of q\n");
    if (ok == 0)
        ft_dprintf(opt.fd[1], "RSA key ok\n");
}