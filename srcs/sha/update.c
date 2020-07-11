/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 15:52:46 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/11 17:20:10 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha.h"
#include "libft.h"

static void SHA224_256PadMessage(t_sha_ctx *ctx,
    uint8_t Pad_Byte)
{
    ctx->bitlen += ctx->index * 8;
  if (ctx->index >= (SHA256_Message_Block_Size-8)) {
    ctx->Message_Block[ctx->index++] = Pad_Byte;
    while (ctx->index < SHA256_Message_Block_Size)
      ctx->Message_Block[ctx->index++] = 0;
    sha256_transform(ctx);
  } else
    ctx->Message_Block[ctx->index++] = Pad_Byte;

  while (ctx->index < (SHA256_Message_Block_Size-8))
    ctx->Message_Block[ctx->index++] = 0;

  ctx->Message_Block[56] = (uint8_t)(ctx->bitlen >> 56);
  ctx->Message_Block[57] = (uint8_t)(ctx->bitlen >> 48);
  ctx->Message_Block[58] = (uint8_t)(ctx->bitlen >> 40);
  ctx->Message_Block[59] = (uint8_t)(ctx->bitlen >> 32);
  ctx->Message_Block[60] = (uint8_t)(ctx->bitlen >> 24);
  ctx->Message_Block[61] = (uint8_t)(ctx->bitlen >> 16);
  ctx->Message_Block[62] = (uint8_t)(ctx->bitlen >> 8);
  ctx->Message_Block[63] = (uint8_t)(ctx->bitlen);

  sha256_transform(ctx);
}

static void SHA224_256Finalize(t_sha_ctx *ctx,
    uint8_t Pad_Byte)
{
  SHA224_256PadMessage(ctx, Pad_Byte);
  ft_bzero(ctx->Message_Block, SHA256_Message_Block_Size);
  ctx->bitlen = 0;
  ctx->Computed = 1;
}

int SHA256Input(t_sha_ctx *ctx, const uint8_t *message_array,
    unsigned int length)
{
  if (!length)
    return shaSuccess;

  if (!ctx || !message_array)
    return shaNull;

  if (ctx->Computed) {
    ctx->Corrupted = shaStateError;
    return shaStateError;
    }

  if (ctx->Corrupted)
     return ctx->Corrupted;

  while (length-- && !ctx->Corrupted) {
    ctx->Message_Block[ctx->index++] =
            (*message_array & 0xFF);

    if (ctx->index == SHA256_Message_Block_Size)
      {
          ctx->bitlen += 512;
      sha256_transform(ctx);
      }

    message_array++;
  }

  return shaSuccess;

}

int SHA224_256ResultN(t_sha_ctx *ctx,
    uint8_t Message_Digest[], int HashSize)
{
  int i;

  if (!ctx || !Message_Digest)
    return shaNull;

  if (ctx->Corrupted)
    return ctx->Corrupted;

  if (!ctx->Computed)
    SHA224_256Finalize(ctx, 0x80);

  for (i = 0; i < HashSize; ++i)
    Message_Digest[i] = (uint8_t)
      (ctx->state[i>>2] >> 8 * ( 3 - ( i & 0x03 ) ));

  return shaSuccess;
}