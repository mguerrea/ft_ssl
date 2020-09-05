/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pbkdf.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 21:36:45 by mguerrea          #+#    #+#             */
/*   Updated: 2020/09/05 12:01:40 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define HLEN 256

#include "des.h"
#include "sha.h"

static void xor_string(unsigned char *dst, unsigned char *src, int len)
{
    int i;

    i = -1;
    while (++i < len)
        dst[i] = dst[i]^src[i];
}

static void concat_index(unsigned char *concat, unsigned char *salt, uint32_t i)
{
    int j;

    j = -1;
    ft_memcpy(concat, salt, 8);
    while (++j < 4)
        concat[8 + j] = (i >> (24 - j * 8)) & 0xFF;
}

#include <stdio.h>

static void iterate(unsigned char *pass, unsigned char *salt, int c, unsigned char *res, uint32_t i)
{
    int j;
    t_hmac hmac;
    unsigned char concat[12];

    ft_bzero(res, 32);
    concat_index(concat, salt, i+1);
    j = -1;
    hmac.k = pass;
    hmac.lk = ft_strlen((const char *)pass);
    hmac.d = concat;
    hmac.ld = 12;
    hmac.t = 32;
    while (++j < c)
    {
        hmac_sha256(&hmac);
        xor_string(res, hmac.out, 32);
        hmac.d = hmac.out;
        hmac.ld = hmac.t;
    }
}

void pbkdf2(unsigned char *pass, unsigned char *salt, int c, int dkLen, unsigned char *DK)
{
    uint32_t l;
    uint32_t i;
    unsigned char res[32];
    int j;

    j = -1;
    l = dkLen / HLEN + ((dkLen % HLEN == 0) ? 0 : 1);
    i = -1;
    while (++i < l && j < dkLen / 8)
    {
        iterate(pass, salt, c, res, i);
        while ((++j + 1) % 32 != 0 && j < dkLen / 8)
            DK[j] = res[j % 32];
    }
}