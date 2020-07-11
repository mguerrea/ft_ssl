/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 17:46:40 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/11 17:59:49 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha.h"
#include "utils.h"

uint32_t sigma(uint32_t x, int n)
{
    if (n == 0)
        return (rot_r(x,7) ^ rot_r(x,18) ^ ((x) >> 3));
    if (n == 1)
        return (rot_r(x,17) ^ rot_r(x,19) ^ ((x) >> 10));
    if (n == 2)
        return (rot_r(x,2) ^ rot_r(x,13) ^ rot_r(x,22));
    if (n == 3)
        return (rot_r(x,6) ^ rot_r(x,11) ^ rot_r(x,25));
    return (0);
}

uint32_t sha_ch(uint32_t x, uint32_t y, uint32_t z)
{
    return (((x) & (y)) ^ (~(x) & (z)));
}

uint32_t sha_maj(uint32_t x, uint32_t y, uint32_t z)
{
    return (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)));
}