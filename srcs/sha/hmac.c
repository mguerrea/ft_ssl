/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmac.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 13:16:22 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/22 13:43:42 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha.h"

void truncate(unsigned char *d1, unsigned char *d2, int len)
{
    int i;
    for (i = 0; i < len; i++)
        d2[i] = d1[i];
}

// static void hmac_inner()
// {
    
// }

void hmac_sha256(unsigned char *k, int lk, unsigned char *d, int ld, unsigned char *out, int t)
{
    t_sha_ctx ictx, octx;
    unsigned char isha[SHA256HashSize], osha[SHA256HashSize];
    unsigned char key[SHA256HashSize];
    unsigned char buf[SHA256_block_Size];
    int i;

    if (lk > SHA256_block_Size)
    {

        t_sha_ctx tctx;

        sha256_init(&tctx);
        sha256_update(&tctx, k, lk);
        sha256_final(&tctx, key, SHA256HashSize);

        k = key;
        lk = SHA256HashSize;
    }

    /**** Inner Digest ****/

    sha256_init(&ictx);

    /* Pad the key for inner digest */
    for (i = 0; i < lk; ++i)
        buf[i] = k[i] ^ 0x36;
    for (i = lk; i < SHA256_block_Size; ++i)
        buf[i] = 0x36;

    sha256_update(&ictx, buf, SHA256_block_Size);
    sha256_update(&ictx, d, ld);

    sha256_final(&ictx, isha, SHA256HashSize);

    /**** Outter Digest ****/

    sha256_init(&octx);

    /* Pad the key for outter digest */

    for (i = 0; i < lk; ++i)
        buf[i] = k[i] ^ 0x5C;
    for (i = lk; i < SHA256_block_Size; ++i)
        buf[i] = 0x5C;

    sha256_update(&octx, buf, SHA256_block_Size);
    sha256_update(&octx, isha, SHA256HashSize);

    sha256_final(&octx, osha, SHA256HashSize);

    /* truncate and print the results */
    t = t > SHA256HashSize ? SHA256HashSize : t;
    truncate(osha, out, t);
    // pr_sha(, out, t);
}
