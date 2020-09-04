/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 17:04:52 by mguerrea          #+#    #+#             */
/*   Updated: 2020/09/04 23:22:34 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"
#include <unistd.h>
#include <stdlib.h>
#include <crypt.h>
#include "ft_printf.h"

void des_init(t_des *des)
{
    des->salted = 0;
    des->mode = 0;
    des->key = 0;
    des->fd[0] = STDIN_FILENO;
    des->fd[1] = STDOUT_FILENO;
    des->b64 = 0;
    des->pass = NULL;
    des->last = 0;
    des->iv = 0;
    ft_bzero(des->salt, 8);
    des->remainder = ' ';
}

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

void         des_read(t_des *des)
{
    unsigned char buff[8];
    int ret;
    char c;

    des->last = 0;
    read(des->fd[0], buff, 1);
    while ((ret = read(des->fd[0], buff + 1, 7)) > 0)
	{
        if (ret == 7 && read(des->fd[0], &c, 1))
        {
            des->func(buff, des, 8);
            buff[0] = c;
        }
        else
            break ;
	}
    des->last = 1;
    des->func(buff, des, ret + 1);
}
