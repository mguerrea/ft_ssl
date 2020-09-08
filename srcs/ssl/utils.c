/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 12:49:21 by mguerrea          #+#    #+#             */
/*   Updated: 2020/09/08 13:06:09 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <unistd.h>

void	random_string(unsigned char *str, int len)
{
	int fd;

	if ((fd = open("/dev/random", O_RDONLY)) < 0)
		return ;
	read(fd, str, len);
	close(fd);
}

void	from_buff_to_int(unsigned char *buff, uint64_t *nb, int len)
{
	int i;

	*nb = 0;
	i = -1;
	while (++i < len)
		*nb = (*nb << 8) | buff[i];
}
