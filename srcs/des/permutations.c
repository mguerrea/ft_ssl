/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 12:29:15 by mguerrea          #+#    #+#             */
/*   Updated: 2020/09/05 15:55:54 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"

extern const int g_pbox[32];
extern int g_ip[64];
extern int g_des_expansion[48];

void	initial_perm(uint64_t *block)
{
	uint64_t	tmp;
	int			i;
	int			rank;

	tmp = 0;
	i = 0;
	while (i < 64)
	{
		rank = g_ip[i] - 1;
		if (1 & (*block >> (63 - rank)))
			tmp |= (1LU << (63 - i));
		i++;
	}
	*block = tmp;
}

void	final_perm(uint64_t *block)
{
	uint64_t	tmp;
	int			i;
	int			rank;

	tmp = 0;
	i = 0;
	while (i < 64)
	{
		rank = g_ip[i] - 1;
		if (1 & (*block >> (63 - i)))
			tmp |= (1LU << (63 - rank));
		i++;
	}
	*block = tmp;
}

void	pbox_perm(uint64_t *block)
{
	uint64_t	tmp;
	int			i;
	int			rank;

	tmp = 0;
	i = 0;
	while (i < 32)
	{
		rank = g_pbox[i] - 1;
		if (1 & (*block >> (31 - rank)))
			tmp |= (1LU << (31 - i));
		i++;
	}
	*block = tmp;
}

void	expand_block(uint64_t *block)
{
	uint64_t	tmp;
	int			i;
	int			rank;

	tmp = 0;
	i = 0;
	while (i < 48)
	{
		rank = g_des_expansion[i] - 1;
		if (1 & (*block >> (31 - rank)))
			tmp |= (1LU << (47 - i));
		i++;
	}
	*block = tmp;
}
