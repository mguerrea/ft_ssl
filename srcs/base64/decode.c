/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 23:39:26 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/17 16:49:57 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64.h"

extern const char *g_base;

static void	b64_padding(unsigned char *str, int fd)
{
	uint32_t nb;

	nb = (uint32_t)(ft_strchr(g_base, str[0]) - g_base) << 6;
	nb |= (uint32_t)(ft_strchr(g_base, str[1]) - g_base);
	if (str[2] == '=')
	{
		ft_putchar_fd((nb >> 4) & 0xff, fd);
	}
	else
	{
		nb = nb << 4 | (uint32_t)(ft_strchr(g_base, str[2]) - g_base) >> 2;
		ft_putchar_fd((nb >> 8) & 0xff, fd);
		ft_putchar_fd(nb & 0xff, fd);
	}
}

static void	trim_spaces(unsigned char *src, unsigned char *dst, int len)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < len)
	{
		if (ft_isspace(src[i]) == 0)
		{
			dst[j] = src[i];
			j++;
		}
		i++;
	}
	dst[j] = 0;
}

static void	convert_chunk(unsigned char *clean, int i, int fd)
{
	char		chunk[4];
	uint32_t	nb;
	int			j;

	chunk[0] = ft_strchr(g_base, clean[i]) - g_base;
	chunk[1] = ft_strchr(g_base, clean[i + 1]) - g_base;
	chunk[2] = ft_strchr(g_base, clean[i + 2]) - g_base;
	chunk[3] = ft_strchr(g_base, clean[i + 3]) - g_base;
	nb = (uint32_t)chunk[0] << 18 | (uint32_t)chunk[1] << 12
		| (uint32_t)chunk[2] << 6 | (uint32_t)chunk[3];
	j = -1;
	while (++j < 4)
		ft_putchar_fd((nb >> (8 * (2 - j))) & 0xff, fd);
}

void		b64_decode(unsigned char *str, unsigned int len, int fd)
{
	unsigned int			i;
	unsigned char			clean[len + 4];
	static unsigned char	buff[4] = "\0";

	i = 0;
	ft_bzero(clean, len + 4);
	ft_strcat((char *)clean, (char *)buff);
	trim_spaces(str, clean + ft_strlen((char *)buff), len);
	while (clean[i] && clean[i + 1] && clean[i + 2] && clean[i + 3]
		&& clean[i + 3] != '=')
	{
		convert_chunk(clean, i, fd);
		i += 4;
	}
	ft_bzero(buff, 4);
	if (ft_strchr((char *)&(clean[i]), '='))
		b64_padding(&(clean[i]), fd);
	else if (clean[i])
		ft_strcat((char *)buff, (char *)&(clean[i]));
}
