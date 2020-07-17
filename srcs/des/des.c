/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 17:04:52 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/17 20:36:14 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

extern int IP[64];
extern int DesExpansion[48];
extern int DesSbox[8][4][16];
extern const int Pbox[32];
extern int PC1[56];
extern const int PC2[48];

const int Rotations[16] = {
    1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};

void initial_perm(uint64_t *block)
{
	uint64_t tmp = 0;
	for (int i = 0; i < 64; i++)
	{
		int rank = IP[i] - 1;
		if (1 & (*block >> (63 - rank)))
			tmp |= (1LU << (63 - i));
	}
	*block = tmp;
}

void final_perm(uint64_t *block)
{
    uint64_t tmp;
    int i;
    int rank;

    tmp = 0;
    i = 0;
    while (i < 64)
    {
        rank = IP[i] - 1;
        if (1 & (*block >> (63 - i)))
            tmp |= (1LU << (63 - rank));
        i++;
    }
    *block = tmp;
}

void pbox_perm(uint64_t *block)
{
    uint64_t tmp;
    int i;
    int rank;

    tmp = 0;
    i = 0;
    while (i < 32)
    {
        rank = Pbox[i] - 1;
        if (1 & (*block >> (31 - rank)))
            tmp |= (1LU << (31 - i));
        i++;
    }
    *block = tmp;
}

void pc1_perm(uint64_t *block)
{
    uint64_t tmp;
    int i;
    int rank;

    tmp = 0;
    i = 0;
    while (i < 56)
    {
        rank = PC1[i] - 1;
        if (1 & (*block >> (63 - rank)))
            tmp |= (1LU << (55 - i));
        i++;
    }
    *block = tmp;
}

void pc2_perm(uint64_t *block)
{
    uint64_t tmp;
    int i;
    int rank;

    tmp = 0;
    i = 0;
    while (i < 48)
    {
        rank = PC2[i] - 1;
        if (1 & (*block >> (55 - rank)))
            tmp |= (1LU << (47 - i));
        i++;
    }
    *block = tmp;
}

void expand_block(uint64_t *block)
{
	uint64_t tmp = 0;
	for(int i = 0; i < 48; i++)
	{
		int rank = DesExpansion[i] - 1;
		if (1 & (*block >> (31 - rank)))
			tmp |= (1LU << (47 - i));
	}
	*block = tmp;
}

uint8_t get_sbox(uint64_t block, int s)
{
	uint8_t sub_block;
    int x;
    int y;

    sub_block = (block >> ((7 - s) * 6)) & 0b111111;
    x = (1 & (sub_block >> 5)) * 2 + (1 & (sub_block >> 0));
    y = (sub_block >> 1) & 0b1111;
	return (DesSbox[s][x][y]);
}

#include "ft_printf.h"

void des_round(uint64_t *block, uint64_t key, int round)
{
    uint64_t right;
    int i;
    uint64_t res;

    right = (*block << 32) >> 32;
    expand_block(&right);
    right = right ^ key;
    i = 0;
    res = 0;
    while (i < 8)
    {
        res = res << 4;
        res |= get_sbox(right, i);
        i++;
    }
    pbox_perm(&res);
    res = res ^ (*block >> 32);
    if (round == 15)
        *block = res << 32 | (*block << 32) >> 32;
    else
        *block = *block << 32 | res;
}

uint64_t half_rotate(uint64_t key, int nb)
{
    uint32_t left;
    uint32_t right;

    left = key >> 28;
    right = key - (left << 28);
    left = ((left << (4 + nb)) >> 4) | left >> (28 - nb);
    right = ((right << (4 + nb)) >> 4) | right >> (28 - nb);
    return ((uint64_t)left << 28 | right);
}

void key_schedule(uint64_t key_s[17], uint64_t key)
{
    int i;

    i = 1;
    pc1_perm(&key);
    key_s[0] = key;
    while (i < 17)
    {
        key_s[i] = half_rotate(key_s[i - 1], Rotations[i - 1]);
        i++;
    }
    i = -1;
    while (++i < 17)
        pc2_perm(&(key_s[i]));
}

void des_encode(uint64_t *block, uint64_t key)
{
    uint64_t key_s[17];
    int i;

    key_schedule(key_s, key);
    i = 0;
    initial_perm(block);
    while (i < 16)
    {
        des_round(block, key_s[i + 1], i);
        i++;
    }
    final_perm(block);
}

#include <unistd.h>
#include <stdlib.h>
#include <crypt.h>


int			ft_des(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    char key[64];
    char plain[64];
    uint64_t cipher = 0;
    uint64_t block = 0;
    uint64_t K = 0x0e329232ea6d0d73;
    for (int i = 0; i < 64; i++)
    {
        key[i] = 0;
        plain[i] = 0;
    }
    setkey(key);
    encrypt(plain, 0);
    for (int i = 0; i < 64; i++)
	{
		cipher <<= 1;
		cipher |= plain[i];
	}
    ft_printf("%llx\n", cipher);
    des_encode(&block, K);
    ft_printf("%llx\n", block);
    return (0);
}