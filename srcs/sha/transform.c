/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 16:33:19 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/12 11:49:39 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha.h"

const static uint32_t g_k[64] = {
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
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

static void	init_sequence(t_sha_ctx *context, uint32_t w[64])
{
	int i;

	i = -1;
	while (++i < 16)
		w[i] = (((uint32_t)context->block[i * 4]) << 24) |
				(((uint32_t)context->block[i * 4 + 1]) << 16) |
				(((uint32_t)context->block[i * 4 + 2]) << 8) |
				(((uint32_t)context->block[i * 4 + 3]));
	i = 15;
	while (++i < 64)
		w[i] = sigma(w[i - 2], 1) + w[i - 7] + sigma(w[i - 15], 0) + w[i - 16];
}

static void	mangle(uint32_t words[8], uint32_t w[64])
{
	int			i;
	uint32_t	temp[2];

	i = -1;
	while (++i < 64)
	{
		temp[0] = words[7] + sigma(words[4], 3) + sha_ch(words[4], words[5],
			words[6]) + g_k[i] + w[i];
		temp[1] = sigma(words[0], 2) + sha_maj(words[0], words[1], words[2]);
		words[7] = words[6];
		words[6] = words[5];
		words[5] = words[4];
		words[4] = words[3] + temp[0];
		words[3] = words[2];
		words[2] = words[1];
		words[1] = words[0];
		words[0] = temp[0] + temp[1];
	}
}

void		sha256_transform(t_sha_ctx *context)
{
	uint32_t	w[64];
	uint32_t	words[8];
	int			i;

	init_sequence(context, w);
	i = -1;
	while (++i < 8)
		words[i] = context->state[i];
	mangle(words, w);
	i = -1;
	while (++i < 8)
		context->state[i] += words[i];
	context->index = 0;
}
