/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miller_rabin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 11:47:34 by user42            #+#    #+#             */
/*   Updated: 2020/12/11 16:03:41 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"

static int miller_witness(uint64_t d, uint64_t n, uint64_t a)
{
    uint64_t x;

    x = pow_mod(a, d, n);
    if (x == 1 || x == n - 1)
        return (1);
    while (d != n - 1 && x != 1)
    {
        x = (x * x) % n;
        d = d * 2;
        if (x == n - 1)
            return (1);
    }
    return (0);
}

int miller_rabin(uint64_t n, float p)
{
    float tmp;
    uint64_t d;

    if (p < 0.5 || p > 1 || n <= 1)
        return (0);
    if (n == 2)
        return (1);
    tmp = 0.5;
    d = n - 1;
    while (d % 2 == 0)
        d /= 2;
    while (1 - tmp < p)
    {
        if (miller_witness(d, n, randint64(2, n - 2)) == 0)
            return (0);
        tmp = tmp / 2;
        ft_printf("+");
    }
    return (1);
}

int miller_rabin64(uint64_t n)
{
    const int base[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    uint64_t d;
    int i;

    if (n <= 1)
        return (0);
    d = n - 1;
    while (d % 2 == 0)
        d /= 2;
    i = -1;
    while (++i < 12)
    {
        if (n == (uint64_t)base[i])
            return (1);
        if (miller_witness(d, n, base[i]) == 0)
            return (0);
    }
    return (1);
}