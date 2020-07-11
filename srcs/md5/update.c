/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 16:01:38 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/11 12:59:53 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"
#include "libft.h"

void	md5_update(t_ctx *context, unsigned char *input, uint32_t input_len)
{
	unsigned int	i;
	uint32_t		index;
	unsigned int	part_len;

	index = ((context->count[0] >> 3) & 0x3F);
	if ((context->count[0] += (input_len << 3)) < (input_len << 3))
		context->count[1]++;
	context->count[1] += (input_len >> 29);
	part_len = 64 - index;
	if (input_len >= part_len)
	{
		ft_memcpy(&context->buffer[index], input, part_len);
		md5_transform(context->state, context->buffer);
		i = part_len;
		while (i + 63 < input_len)
		{
			md5_transform(context->state, &input[i]);
			i += 64;
		}
		index = 0;
	}
	else
		i = 0;
	ft_memcpy(&context->buffer[index], &input[i], input_len - i);
}

void	md5_final(unsigned char digest[16], t_ctx *context)
{
	unsigned char		bits[8];
	unsigned int		index;
	unsigned int		pad_len;
	const unsigned char	padding[64] = {
		0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	md5_encode(bits, context->count, 8);
	index = (unsigned int)((context->count[0] >> 3) & 0x3f);
	pad_len = (index < 56) ? (56 - index) : (120 - index);
	md5_update(context, (unsigned char *)padding, pad_len);
	md5_update(context, bits, 8);
	md5_encode(digest, context->state, 16);
	ft_bzero(context, sizeof(*context));
}
