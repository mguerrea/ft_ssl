/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decode_buff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 13:33:42 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/20 20:05:09 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64.h"

extern const char *g_base;

static void	b64_padding(unsigned char *str, unsigned char *output)
{
	uint32_t nb;

	nb = (uint32_t)(ft_strchr(g_base, str[0]) - g_base) << 6;
	nb |= (uint32_t)(ft_strchr(g_base, str[1]) - g_base);
	if (str[2] == '=')
	{
        output[0] = (nb >> 4) & 0xff;
	}
	else
	{
		nb = nb << 4 | (uint32_t)(ft_strchr(g_base, str[2]) - g_base) >> 2;
		output[0] = (nb >> 8) & 0xff;
        output[1] = nb & 0xff;
	}
}

static void	convert_chunk(unsigned char *clean, unsigned char *decoded)
{
	int			j;
    unsigned char chunk[4];
    uint64_t nb;

	chunk[0] = ft_strchr(g_base, clean[0]) - g_base;
	chunk[1] = ft_strchr(g_base, clean[0 + 1]) - g_base;
	chunk[2] = ft_strchr(g_base, clean[0 + 2]) - g_base;
	chunk[3] = ft_strchr(g_base, clean[0 + 3]) - g_base;
	nb = (uint32_t)chunk[0] << 18 | (uint32_t)chunk[1] << 12
		| (uint32_t)chunk[2] << 6 | (uint32_t)chunk[3];
	j = -1;
	while (++j < 3)
        decoded[j] = (nb >> (8 * (2 - j))) & 0xff;
}

void		b64_decode_buff(unsigned char *str, unsigned int len,
    unsigned char *output)
{
	unsigned int			i;
    unsigned char decoded[3];
    int j;

	i = 0;
	while (i < (len - 3) && str[i + 3] != '=')
	{
		convert_chunk(&(str[i]), decoded);
        j = -1;
        while (++j < 3)
            output[(i/4)*3+j] = decoded[j];
		i += 4;
	}
    b64_padding(&(str[i]), &(output[i/4 * 3]));
}