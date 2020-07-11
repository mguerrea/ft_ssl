/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 15:52:46 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/11 18:24:37 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha.h"
#include "libft.h"

static void SHA224_256PadMessage(t_sha_ctx *ctx,
    uint8_t Pad_Byte)
{
    ctx->bitlen += ctx->index * 8;
  if (ctx->index >= (SHA256_block_Size-8)) {
    ctx->block[ctx->index++] = Pad_Byte;
    while (ctx->index < SHA256_block_Size)
      ctx->block[ctx->index++] = 0;
    sha256_transform(ctx);
  } else
    ctx->block[ctx->index++] = Pad_Byte;

  while (ctx->index < (SHA256_block_Size-8))
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

static void SHA224_256Finalize(t_sha_ctx *ctx,
    uint8_t Pad_Byte)
{
  SHA224_256PadMessage(ctx, Pad_Byte);
  ft_bzero(ctx->block, SHA256_block_Size);
  ctx->bitlen = 0;
  ctx->computed = 1;
}

void sha256_update(t_sha_ctx *ctx, const uint8_t *to_hash,
    unsigned int length)
{
  while (length--) 
  {
    ctx->block[ctx->index++] =
            (*to_hash & 0xFF);

    if (ctx->index == SHA256_block_Size)
      {
          ctx->bitlen += 512;
      sha256_transform(ctx);
      }

    to_hash++;
  }
}

int SHA224_256ResultN(t_sha_ctx *ctx,
    uint8_t Message_Digest[], int HashSize)
{
  int i;

  if (!ctx->computed)
    SHA224_256Finalize(ctx, 0x80);

  for (i = 0; i < HashSize; ++i)
    Message_Digest[i] = (uint8_t)
      (ctx->state[i>>2] >> 8 * ( 3 - ( i & 0x03 ) ));

  return shaSuccess;
}