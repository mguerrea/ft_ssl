/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 12:19:24 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/17 16:47:24 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64.h"

extern const char *g_base;
extern int g_count;

static void	convert_chunk(char chunk[4], uint32_t nb, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		chunk[i] = g_base[(nb >> (6 * (len - i - 1))) & 0b111111];
		i++;
	}
	while (i < 4)
	{
		chunk[i] = '=';
		i++;
	}
}

static void	b64_padding(unsigned char *str, unsigned int len, int fd)
{
	uint32_t	nb;
	char		chunk[4];
	int			i;

	i = -1;
	if (len == 0)
		return ;
	if (len == 1)
		nb = (uint32_t)str[0] << 4;
	else
		nb = (uint32_t)str[0] << 10 | (uint32_t)str[1] << 2;
	convert_chunk(chunk, nb, len + 1);
	while (++i < 4)
		ft_putchar_fd(chunk[i], fd);
	g_count += 4;
}

void		b64_encode(unsigned char *str, unsigned int len, int fd)
{
	uint32_t		nb;
	char			chunk[4];
	int				i;
	int				j;

	i = 0;
	while (i < (int)len - 2)
	{
		nb = (uint32_t)str[i] << 16 | (uint32_t)str[i + 1] << 8
			| (uint32_t)str[i + 2];
		convert_chunk(chunk, nb, 4);
		j = -1;
		while (++j < 4)
			ft_putchar_fd(chunk[j], fd);
		i += 3;
		g_count += 4;
		if (g_count % 64 == 0)
			ft_putchar_fd('\n', fd);
	}
	b64_padding(&(str[i]), len - i, fd);
}
