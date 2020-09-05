/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmac.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 13:16:22 by mguerrea          #+#    #+#             */
/*   Updated: 2020/09/05 12:50:20 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha.h"
#include "libft.h"

static void	hmac_inner(t_hmac *hmac, unsigned char *isha, uint8_t byte)
{
	int				i;
	t_sha_ctx		ictx;
	unsigned char	buf[SHA256_block_Size];

	sha256_init(&ictx);
	i = -1;
	while (++i < hmac->lk)
		buf[i] = hmac->k[i] ^ byte;
	i--;
	while (++i < SHA256_block_Size)
		buf[i] = byte;
	sha256_update(&ictx, buf, SHA256_block_Size);
	sha256_update(&ictx, hmac->d, hmac->ld);
	sha256_final(&ictx, isha, SHA256HashSize);
}

void		hmac_sha256(t_hmac *hmac)
{
	unsigned char	isha[SHA256HashSize];
	unsigned char	key[SHA256HashSize];
	t_sha_ctx		tctx;

	if (hmac->lk > SHA256_block_Size)
	{
		sha256_init(&tctx);
		sha256_update(&tctx, hmac->k, hmac->lk);
		sha256_final(&tctx, key, SHA256HashSize);
		hmac->k = key;
		hmac->lk = SHA256HashSize;
	}
	hmac_inner(hmac, isha, 0x36);
	hmac->d = isha;
	hmac->ld = SHA256HashSize;
	hmac_inner(hmac, isha, 0x5c);
	hmac->t = hmac->t > SHA256HashSize ? SHA256HashSize : hmac->t;
	ft_memcpy(hmac->out, isha, hmac->t);
}
