/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 16:16:48 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/10 16:18:10 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

uint32_t k[] = {
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
        0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
        0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
        0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
        0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
        0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
        0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
        0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
        0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
        0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
        0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
        0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

static void md5_round1(uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d, uint32_t x[16])
{
	int i;

	i = 0;
	while (i < 16)
	{
		if (i % 4 == 0)
			md5_op(a, md5_F(*b, *c, *d) + x[i] + k[i], 7, *b);
		if (i % 4 == 1)
			md5_op(d, md5_F(*a, *b, *c) + x[i] + k[i], 12, *a);
		if (i % 4 == 2)
			md5_op(c, md5_F(*d, *a, *b) + x[i] + k[i], 17, *d);
		if (i % 4 == 3)
			md5_op(b, md5_F(*c, *d, *a) + x[i] + k[i], 22, *c);
		i++;
	}
}

static void md5_round2(uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d, uint32_t x[16])
{
	int i;

	i = 0;
	while (i < 16)
	{
		if (i % 4 == 0)
			md5_op(a, md5_G(*b, *c, *d) + x[(i * 5 +1)% 16] + k[i+16], 5, *b);
		if (i % 4 == 1)
			md5_op(d, md5_G(*a, *b, *c) + x[(i * 5 + 1) % 16] + k[i+16], 9, *a);
		if (i % 4 == 2)
			md5_op(c, md5_G(*d, *a, *b) + x[(i * 5 + 1) % 16] + k[i+16], 14, *d);
		if (i % 4 == 3)
			md5_op(b, md5_G(*c, *d, *a) + x[(i * 5 + 1) % 16] + k[i+16], 20, *c);
		i++;
	}
}

static void md5_round3(uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d, uint32_t x[16])
{
	int i;

	i = 0;
	while (i < 16)
	{
		if (i % 4 == 0)
			md5_op(a, md5_H(*b, *c, *d) + x[(i * 3 + 5) % 16] + k[i+32], 4, *b);
		if (i % 4 == 1)
			md5_op(d, md5_H(*a, *b, *c) + x[(i * 3 + 5) % 16] + k[i+32], 11, *a);
		if (i % 4 == 2)
			md5_op(c, md5_H(*d, *a, *b) + x[(i * 3 + 5) % 16] + k[i+32], 16, *d);
		if (i % 4 == 3)
			md5_op(b, md5_H(*c, *d, *a) + x[(i * 3 + 5) % 16] + k[i+32], 23, *c);
		i++;
	}
}

static void md5_round4(uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d, uint32_t x[16])
{
	int i;

	i = 0;
	while (i < 16)
	{
		if (i % 4 == 0)
			md5_op(a, md5_I(*b, *c, *d) + x[(i * 7) % 16] + k[i+48], 6, *b);
		if (i % 4 == 1)
			md5_op(d, md5_I(*a, *b, *c) + x[(i * 7) % 16] + k[i+48], 10, *a);
		if (i % 4 == 2)
			md5_op(c, md5_I(*d, *a, *b) + x[(i * 7) % 16] + k[i+48], 15, *d);
		if (i % 4 == 3)
			md5_op(b, md5_I(*c, *d, *a) + x[(i * 7) % 16] + k[i+48], 21, *c);
		i++;
	}
}

void md5_transform(uint32_t state[4], unsigned char block[64])
{
	uint32_t a = state[0];
	uint32_t b = state[1];
	uint32_t c = state[2];
	uint32_t d = state[3];
	uint32_t x[16];

	md5_decode(x, block, 64);
	md5_round1(&a, &b, &c, &d, x);
	md5_round2(&a, &b, &c, &d, x);
	md5_round3(&a, &b, &c, &d, x);
	md5_round4(&a, &b, &c, &d, x);

	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;
	ft_bzero(x, sizeof(x));
}