/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 12:29:15 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/19 12:32:06 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"

extern const int Pbox[32];
extern int IP[64];
extern int DesExpansion[48];

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
