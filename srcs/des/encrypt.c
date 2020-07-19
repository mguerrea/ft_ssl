/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encrypt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 12:33:18 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/19 16:03:53 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"

extern int DesSbox[8][4][16];

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

void des_round(uint64_t *block, uint64_t key)
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
    *block = *block << 32 | res;
}

void des_encrypt_block(uint64_t *block, uint64_t key)
{
    uint64_t key_s[17];
    int i;

    key_schedule(key_s, key);
    i = 0;
    initial_perm(block);
    while (i < 16)
    {
        des_round(block, key_s[i + 1]);
        i++;
    }
    *block = (*block << 32) | (*block >> 32);
    final_perm(block);
}

void des_decrypt_block(uint64_t *block, uint64_t key)
{
    uint64_t key_s[17];
    int i;

    key_schedule(key_s, key);
    i = 16;
    initial_perm(block);
    while (i > 0)
    {
        des_round(block, key_s[i]);
        i--;
    }
    *block = (*block << 32) | (*block >> 32);
    final_perm(block);
}
