/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 16:01:38 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/10 14:41:47 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"
#include "libft.h"

void md5_update(t_ctx *context, unsigned char *input, unsigned int inputLen)
{
    unsigned int i;
    unsigned int index;
    unsigned int partLen;

    index = (unsigned int)((context->count[0] >> 3) & 0x3F);

    /* Update number of bits */
    if ((context->count[0] += ((uint32_t)inputLen << 3)) < ((uint32_t)inputLen << 3))
        context->count[1]++;
    context->count[1] += ((uint32_t)inputLen >> 29);

    partLen = 64 - index;

    /* Transform as many times as possible.
*/
    if (inputLen >= partLen)
    {
        ft_memcpy((unsigned char *)&context->buffer[index], (unsigned char *)input, partLen);
        md5_transform(context->state, context->buffer);

        for (i = partLen; i + 63 < inputLen; i += 64)
            md5_transform(context->state, &input[i]);

        index = 0;
    }
    else
        i = 0;

    /* Buffer remaining input */
    ft_memcpy((unsigned char *)&context->buffer[index], (unsigned char *)&input[i],
               inputLen - i);
}

void md5_final (unsigned char digest[16], t_ctx *context)
{
  unsigned char bits[8];
  unsigned int index;
  unsigned int padLen;
  const unsigned char PADDING[64] = {
  0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


  /* Save number of bits */
  md5_encode (bits, context->count, 8);

  /* Pad out to 56 mod 64.
*/
  index = (unsigned int)((context->count[0] >> 3) & 0x3f);
  padLen = (index < 56) ? (56 - index) : (120 - index);
  md5_update (context, (unsigned char *)PADDING, padLen);

  /* Append length (before padding) */
  md5_update (context, bits, 8);
  /* Store state in digest */
  md5_encode (digest, context->state, 16);

  /* Zeroize sensitive information.
*/
	ft_bzero(context, sizeof(*context));
}

