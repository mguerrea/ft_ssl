/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pbkdf2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 21:36:45 by mguerrea          #+#    #+#             */
/*   Updated: 2020/12/16 14:52:59 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define HLEN 256

#include "des.h"
#include "sha.h"

static void	xor_string(unsigned char *dst, unsigned char *src)
{
	uint64_t *lldst;
	uint64_t *llsrc;

	llsrc = (uint64_t *)src;
	lldst = (uint64_t *)dst;
	lldst[0] ^= llsrc[0];
	lldst[1] ^= llsrc[1];
	lldst[2] ^= llsrc[2];
	lldst[3] ^= llsrc[3];
}

static void	concat_index(unsigned char *concat, unsigned char *salt, uint32_t i)
{
	int j;

	j = -1;
	ft_memcpy(concat, salt, 8);
	while (++j < 4)
		concat[8 + j] = (i >> (24 - j * 8)) & 0xFF;
}

static void	iterate(t_pbkdf *ctx, unsigned char *res, uint32_t i)
{
	int				j;
	t_hmac			hmac;
	unsigned char	concat[12];

	ft_bzero(res, 32);
	concat_index(concat, ctx->salt, i + 1);
	j = -1;
	hmac.k = ctx->pass;
	hmac.lk = ft_strlen((const char *)ctx->pass);
	hmac.d = concat;
	hmac.ld = 12;
	hmac.t = 32;
	while (++j < ctx->c)
	{
		hmac_sha256(&hmac);
		xor_string(res, hmac.out);
		hmac.d = hmac.out;
		hmac.ld = hmac.t;
	}
}

void		pbkdf2(t_pbkdf *ctx)
{
	uint32_t		l;
	uint32_t		i;
	unsigned char	res[32];

	l = ctx->keylen / HLEN + ((ctx->keylen % HLEN == 0) ? 0 : 1);
	i = -1;
	while (++i < l && (int)i * 32 < ctx->keylen / 8)
	{
		iterate(ctx, res, i);
		ft_memcpy(ctx->key + i * 32, res, ((int)i * 32 + 32 < ctx->keylen / 8)
			? 32 : ctx->keylen / 8 - i * 32);
	}
}
