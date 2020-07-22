/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 17:04:52 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/22 14:05:09 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"
#include <unistd.h>
#include <stdlib.h>
#include <crypt.h>
#include "ft_printf.h"

void des_padding(uint64_t *block, uint8_t len)
{
    int i;

    i = 0;
    while (i < len)
    {
        *block = *block << 8 | len;
        i++;
    }
}

void des_remove_padding(uint64_t *block, int *len)
{
    uint8_t pad;
    int i;

    i = 0;
    pad = *block & 0xff;
    if (pad > 8)
        return ;
    while (i < pad)
    {
        if (((*block >> (i * 8)) & 0xff) != pad)
            return ;
        i++;
    }
    *block = *block >> pad * 8;
    *len = *len - pad;
}

void         des_read(t_des des,
    void	(*func)(unsigned char *, t_des, int))
{
    unsigned char buff[8];
    int ret;
    char c;

    des.last = 0;
    read(des.fd[0], buff, 1);
    while ((ret = read(des.fd[0], buff + 1, 7)) > 0)
	{
        if (ret == 7 && read(des.fd[0], &c, 1))
        {
            func(buff, des, 8);
            buff[0] = c;
        }
        else
            break ;
	}
    des.last = 1;
    func(buff, des, ret + 1);
}
