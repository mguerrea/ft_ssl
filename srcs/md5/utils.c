/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 15:45:03 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/12 12:08:42 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

void	md5_encode(unsigned char *output, uint32_t *input, unsigned int len)
{
	unsigned int i;
	unsigned int j;

	j = 0;
	i = 0;
	while (j < len)
	{
		output[j] = (unsigned char)(input[i] & 0xff);
		output[j + 1] = (unsigned char)((input[i] >> 8) & 0xff);
		output[j + 2] = (unsigned char)((input[i] >> 16) & 0xff);
		output[j + 3] = (unsigned char)((input[i] >> 24) & 0xff);
		i++;
		j += 4;
	}
}

void	md5_decode(uint32_t *output, unsigned char *input, unsigned int len)
{
	unsigned int i;
	unsigned int j;

	j = 0;
	i = 0;
	while (j < len)
	{
		output[i] = ((uint32_t)input[j]) | (((uint32_t)input[j + 1]) << 8) |
			(((uint32_t)input[j + 2]) << 16) | (((uint32_t)input[j + 3]) << 24);
		i++;
		j += 4;
	}
}

void	md5_init(t_ctx *context)
{
	context->count[0] = 0;
	context->count[1] = 0;
	context->state[0] = 0x67452301;
	context->state[1] = 0xefcdab89;
	context->state[2] = 0x98badcfe;
	context->state[3] = 0x10325476;
}
