/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 12:32:24 by mguerrea          #+#    #+#             */
/*   Updated: 2020/12/12 12:42:05 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"

uint64_t pow_mod(uint64_t x, uint64_t n, uint64_t mod)
{
    if (n == 0)
        return (1);
    else if (n == 1)
        return (x);
    else if (n % 2 == 0)
        return (pow_mod((x * x) % mod, n / 2, mod));
    else
        return (x * pow_mod((x * x) % mod, (n - 1) / 2, mod) % mod);
}

uint64_t mul_inv(uint64_t a, uint64_t b, t_int64 x[3], uint64_t v[4])
{
    while (a > 1)
    {
        if (b == 0) 
            return 0;
        v[1] = a / b;
        v[2] = b;
        b = a % b;
        a = v[2];
        x[2] = x[0];
        v[3] = v[1] * x[0].val;
        if (x[0].neg != x[1].neg)
        {
            x[0].val = x[1].val + v[3];
            x[0].neg = x[1].neg;
        }
        else
        {
            x[0].val = (x[1].val > v[3]) ? x[1].val - v[3] : v[3] - x[1].val;
            x[0].neg = (x[1].val > v[3]) ? x[1].neg : !x[0].neg;
        }
        x[1] = x[2];
    }
    return x[1].neg ? (v[0] - x[1].val) : x[1].val;
}

uint64_t inv_mod(uint64_t a, uint64_t n)
{
    t_int64 x[3];
    uint64_t v[4];

    x[0].neg = 0;
    x[1].neg = 0;
    x[0].val = 0;
    x[1].val = 1;
    v[0] = n;
    if (n <= 1)
        return (0);
    return(mul_inv(a,n,x,v));

}