/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 15:52:46 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/12 12:52:29 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha.h"
#include "libft.h"

void		sha256_init(t_sha_ctx *context)
{
	context->index = 0;
	context->bitlen = 0;
	context->state[0] = 0x6a09e667;
	context->state[1] = 0xbb67ae85;
	context->state[2] = 0x3c6ef372;
	context->state[3] = 0xa54ff53a;
	context->state[4] = 0x510e527f;
	context->state[5] = 0x9b05688c;
	context->state[6] = 0x1f83d9ab;
	context->state[7] = 0x5be0cd19;
}

static void	sha256_padding(t_sha_ctx *ctx, uint8_t pad)
{
	ctx->bitlen += ctx->index * 8;
	if (ctx->index >= (SHA256_block_Size - 8))
	{
		ctx->block[ctx->index++] = pad;
		while (ctx->index < SHA256_block_Size)
			ctx->block[ctx->index++] = 0;
		sha256_transform(ctx);
	}
	else
		ctx->block[ctx->index++] = pad;
	while (ctx->index < (SHA256_block_Size - 8))
		ctx->block[ctx->index++] = 0;
	ctx->block[56] = (uint8_t)(ctx->bitlen >> 56);
	ctx->block[57] = (uint8_t)(ctx->bitlen >> 48);
	ctx->block[58] = (uint8_t)(ctx->bitlen >> 40);
	ctx->block[59] = (uint8_t)(ctx->bitlen >> 32);
	ctx->block[60] = (uint8_t)(ctx->bitlen >> 24);
	ctx->block[61] = (uint8_t)(ctx->bitlen >> 16);
	ctx->block[62] = (uint8_t)(ctx->bitlen >> 8);
	ctx->block[63] = (uint8_t)(ctx->bitlen);
	sha256_transform(ctx);
}

void		sha256_update(t_sha_ctx *ctx, const uint8_t *to_hash,
	unsigned int length)
{
	while (length--)
	{
		ctx->block[ctx->index++] = (*to_hash & 0xFF);
		if (ctx->index == SHA256_block_Size)
		{
			ctx->bitlen += 512;
			sha256_transform(ctx);
		}
		to_hash++;
	}
}

void		sha256_final(t_sha_ctx *ctx, uint8_t digest[], int hash_size)
{
	int i;

	sha256_padding(ctx, 0x80);
	ft_bzero(ctx->block, SHA256_block_Size);
	ctx->bitlen = 0;
	i = -1;
	while (++i < hash_size)
		digest[i] = (uint8_t)(ctx->state[i >> 2] >> 8 * (3 - (i & 0x03)));
}
