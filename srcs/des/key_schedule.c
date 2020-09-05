/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_schedule.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 12:26:17 by mguerrea          #+#    #+#             */
/*   Updated: 2020/09/05 13:10:38 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"

extern int g_pc1[56];
extern const int g_pc2[48];

void		pc1_perm(uint64_t *block)
{
	uint64_t	tmp;
	int			i;
	int			rank;

	tmp = 0;
	i = 0;
	while (i < 56)
	{
		rank = g_pc1[i] - 1;
		if (1 & (*block >> (63 - rank)))
			tmp |= (1LU << (55 - i));
		i++;
	}
	*block = tmp;
}

void		pc2_perm(uint64_t *block)
{
	uint64_t	tmp;
	int			i;
	int			rank;

	tmp = 0;
	i = 0;
	while (i < 48)
	{
		rank = g_pc2[i] - 1;
		if (1 & (*block >> (55 - rank)))
			tmp |= (1LU << (47 - i));
		i++;
	}
	*block = tmp;
}

uint64_t	half_rotate(uint64_t key, int nb)
{
	uint32_t left;
	uint32_t right;

	left = key >> 28;
	right = key - (left << 28);
	left = ((left << (4 + nb)) >> 4) | left >> (28 - nb);
	right = ((right << (4 + nb)) >> 4) | right >> (28 - nb);
	return ((uint64_t)left << 28 | right);
}

void		key_schedule(uint64_t key_s[17], uint64_t key)
{
	int			i;
	const int	rotations[16] = {
	1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

	i = 1;
	pc1_perm(&key);
	key_s[0] = key;
	while (i < 17)
	{
		key_s[i] = half_rotate(key_s[i - 1], rotations[i - 1]);
		i++;
	}
	i = -1;
	while (++i < 17)
		pc2_perm(&(key_s[i]));
}
