/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 16:16:48 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/12 11:43:15 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

uint32_t	g_x[16];
const static uint32_t	g_k[] = {
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

static void	md5_round1(uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d)
{
	int i;

	i = 0;
	while (i < 16)
	{
		if (i % 4 == 0)
			md5_op(a, md5_f(*b, *c, *d) + g_x[i] + g_k[i], 7, *b);
		if (i % 4 == 1)
			md5_op(d, md5_f(*a, *b, *c) + g_x[i] + g_k[i], 12, *a);
		if (i % 4 == 2)
			md5_op(c, md5_f(*d, *a, *b) + g_x[i] + g_k[i], 17, *d);
		if (i % 4 == 3)
			md5_op(b, md5_f(*c, *d, *a) + g_x[i] + g_k[i], 22, *c);
		i++;
	}
}

static void	md5_round2(uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d)
{
	int i;

	i = 16;
	while (i < 32)
	{
		md5_op(a, md5_g(*b, *c, *d) + g_x[(i * 5 + 1) % 16] + g_k[i], 5, *b);
		i++;
		md5_op(d, md5_g(*a, *b, *c) + g_x[(i * 5 + 1) % 16] + g_k[i], 9, *a);
		i++;
		md5_op(c, md5_g(*d, *a, *b) + g_x[(i * 5 + 1) % 16] + g_k[i], 14, *d);
		i++;
		md5_op(b, md5_g(*c, *d, *a) + g_x[(i * 5 + 1) % 16] + g_k[i], 20, *c);
		i++;
	}
}

static void	md5_round3(uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d)
{
	int i;

	i = 32;
	while (i < 48)
	{
		md5_op(a, md5_h(*b, *c, *d) + g_x[(i * 3 + 5) % 16] + g_k[i], 4, *b);
		i++;
		md5_op(d, md5_h(*a, *b, *c) + g_x[(i * 3 + 5) % 16] + g_k[i], 11, *a);
		i++;
		md5_op(c, md5_h(*d, *a, *b) + g_x[(i * 3 + 5) % 16] + g_k[i], 16, *d);
		i++;
		md5_op(b, md5_h(*c, *d, *a) + g_x[(i * 3 + 5) % 16] + g_k[i], 23, *c);
		i++;
	}
}

static void	md5_round4(uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d)
{
	int i;

	i = 48;
	while (i < 64)
	{
		if (i % 4 == 0)
			md5_op(a, md5_i(*b, *c, *d) + g_x[(i * 7) % 16] + g_k[i], 6, *b);
		if (i % 4 == 1)
			md5_op(d, md5_i(*a, *b, *c) + g_x[(i * 7) % 16] + g_k[i], 10, *a);
		if (i % 4 == 2)
			md5_op(c, md5_i(*d, *a, *b) + g_x[(i * 7) % 16] + g_k[i], 15, *d);
		if (i % 4 == 3)
			md5_op(b, md5_i(*c, *d, *a) + g_x[(i * 7) % 16] + g_k[i], 21, *c);
		i++;
	}
}

void		md5_transform(uint32_t state[4], unsigned char block[64])
{
	uint32_t a;
	uint32_t b;
	uint32_t c;
	uint32_t d;

	a = state[0];
	b = state[1];
	c = state[2];
	d = state[3];
	md5_decode(g_x, block, 64);
	md5_round1(&a, &b, &c, &d);
	md5_round2(&a, &b, &c, &d);
	md5_round3(&a, &b, &c, &d);
	md5_round4(&a, &b, &c, &d);
	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;
	ft_bzero(g_x, sizeof(g_x));
}
