/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 11:55:09 by mguerrea          #+#    #+#             */
/*   Updated: 2020/12/16 17:34:23 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"
#include "ft_printf.h"

void	digest_print(char *format, char *str, unsigned char *digest, t_opt opt)
{
	unsigned int i;

	i = 0;
	if (!(opt & REV) && !(opt & QUIET))
		ft_printf(format, str);
	while (i < g_hash_size)
	{
		ft_printf("%02x", digest[i]);
		i++;
	}
	if (opt & REV && ft_strchr(format, '\"') && !(opt & QUIET))
		ft_printf(" \"%s\"", str);
	else if (opt & REV && !(opt & QUIET))
		ft_printf(" %s", str);
	ft_printf("\n");
}

void	print_block(uint64_t block, int fd)
{
	char	buff[8];
	int		i;

	i = -1;
	while (++i < 8)
		buff[i] = (block >> (56 - 8 * i)) & 0xff;
	write(fd, buff, 8);
}

void	print_hex(unsigned char *str, int len, int fd)
{
	int i;

	i = -1;
	while (++i < len)
		ft_dprintf(fd, "%02X", str[i]);
}
