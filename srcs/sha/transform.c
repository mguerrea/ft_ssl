/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 16:33:19 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/11 17:20:31 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha.h"

#define ROTLEFT(a,b) (((a) << (b)) | ((a) >> (32-(b))))
#define ROTRIGHT(a,b) (((a) >> (b)) | ((a) << (32-(b))))

#define SHA_Ch(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
#define SHA_Maj(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define SHA256_SIGMA0(x) (ROTRIGHT(x,2) ^ ROTRIGHT(x,13) ^ ROTRIGHT(x,22))
#define SHA256_SIGMA1(x) (ROTRIGHT(x,6) ^ ROTRIGHT(x,11) ^ ROTRIGHT(x,25))
#define SHA256_sigma0(x) (ROTRIGHT(x,7) ^ ROTRIGHT(x,18) ^ ((x) >> 3))
#define SHA256_sigma1(x) (ROTRIGHT(x,17) ^ ROTRIGHT(x,19) ^ ((x) >> 10))

void sha256_transform(t_sha_ctx *context)
{
  /* Constants defined in FIPS-180-2, section 4.2.2 */
  const uint32_t K[64] = {
      0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b,
      0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01,
      0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7,
      0xc19bf174, 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
      0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 0x983e5152,
      0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
      0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc,
      0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
      0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819,
      0xd6990624, 0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08,
      0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f,
      0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
      0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
  };
  int        t, t4;                   /* Loop counter */
  uint32_t   temp1, temp2;            /* Temporary word value */
  uint32_t   W[64];                   /* Word sequence */
  uint32_t   A, B, C, D, E, F, G, H;  /* Word buffers */

  /*
   * Initialize the first 16 words in the array W
   */
  for (t = t4 = 0; t < 16; t++, t4 += 4)
    W[t] = (((uint32_t)context->Message_Block[t4]) << 24) |
           (((uint32_t)context->Message_Block[t4 + 1]) << 16) |
           (((uint32_t)context->Message_Block[t4 + 2]) << 8) |
           (((uint32_t)context->Message_Block[t4 + 3]));
    
    for (t = 16; t < 64; t++)
    W[t] = SHA256_sigma1(W[t-2]) + W[t-7] +
        SHA256_sigma0(W[t-15]) + W[t-16];

  A = context->state[0];
  B = context->state[1];
  C = context->state[2];
  D = context->state[3];
  E = context->state[4];
  F = context->state[5];
  G = context->state[6];
  H = context->state[7];

  for (t = 0; t < 64; t++) {
    temp1 = H + SHA256_SIGMA1(E) + SHA_Ch(E,F,G) + K[t] + W[t];
    temp2 = SHA256_SIGMA0(A) + SHA_Maj(A,B,C);
    H = G;
    G = F;
    F = E;
    E = D + temp1;
    D = C;
    C = B;
    B = A;
    A = temp1 + temp2;
  }

  context->state[0] += A;
  context->state[1] += B;
  context->state[2] += C;
  context->state[3] += D;
  context->state[4] += E;
  context->state[5] += F;
  context->state[6] += G;
  context->state[7] += H;

  context->index = 0;
}
