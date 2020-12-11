/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 12:32:24 by mguerrea          #+#    #+#             */
/*   Updated: 2020/12/11 13:35:10 by mguerrea         ###   ########.fr       */
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