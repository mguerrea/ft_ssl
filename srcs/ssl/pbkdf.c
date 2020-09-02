/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pbkdf.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 21:36:45 by mguerrea          #+#    #+#             */
/*   Updated: 2020/09/02 12:52:13 by mguerrea         ###   ########.fr       */
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

static void iterate(unsigned char *pass, unsigned char *salt, int c, unsigned char *res)
{
    int i;
    t_hmac hmac;

    ft_bzero(res, 32);
      i = -1;
    hmac.k = pass;
    hmac.lk = ft_strlen((const char *)pass);
    hmac.d = salt;
    hmac.ld = 8;
    hmac.t = 32;
    while (++i < c)
    {
        hmac_sha256(&hmac);
        xor_string(res, hmac.out, 32);
        hmac.d = hmac.out;
        hmac.ld = hmac.t;
    }
}

void pbkdf2(unsigned char *pass, unsigned char *salt, int c, int dkLen, unsigned char *DK)
{
    int l;
    int i;
    unsigned char res[32];
    int j;

    j = -1;
    l = dkLen / HLEN + ((dkLen % HLEN == 0) ? 0 : 1);
    i = -1;
    while (++i < l && j < dkLen / 8)
    {
        iterate(pass, salt, c, res);
        while ((++j + 1) % 32 != 0 && j < dkLen / 8)
            DK[j] = res[j % 32];
    }
}