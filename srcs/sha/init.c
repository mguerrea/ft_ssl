/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 13:19:23 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/12 13:28:00 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha.h"

void		sha256_init(t_sha_ctx *context)
{
	context->index = 0;
	context->bitlen = 0;
	context->state[0] = 0x6a09e667;
	context->state[1] = 0xbb67ae85;
	context->state[2] = 0x3c6ef372;
	context->state[3] = 0xa54ff53a;
	context->state[4] = 0x510e527f;
	context->state[5] = 0x9b05688c;
	context->state[6] = 0x1f83d9ab;
	context->state[7] = 0x5be0cd19;
}

void		sha224_init(t_sha_ctx *context)
{
	context->index = 0;
	context->bitlen = 0;
	context->state[0] = 0xC1059ED8;
	context->state[1] = 0x367CD507;
	context->state[2] = 0x3070DD17;
	context->state[3] = 0xF70E5939;
	context->state[4] = 0xFFC00B31;
	context->state[5] = 0x68581511;
	context->state[6] = 0x64F98FA7;
	context->state[7] = 0xBEFA4FA4;
}
