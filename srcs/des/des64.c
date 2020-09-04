/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des64.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 14:04:56 by mguerrea          #+#    #+#             */
/*   Updated: 2020/09/04 23:08:30 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"

static int manage_block(t_des des, unsigned char *buff,
                        void (*func)(unsigned char *, t_des *, int))
{
    unsigned char c;
    int i;
    unsigned char buff_des[24];

    b64_decode_buff(buff, 32, buff_des);
    i = 0;
    c = ' ';
    while ((read(des.fd[0], &c, 1)) > 0 && ft_isspace(c));
    func(buff_des, &des, 8);
    func(buff_des + 8, &des, 8);
    if (ft_isspace(c))
        des.last = 1;
    else
        buff[i++] = c;
    func(buff_des + 16, &des, 8);
    return (i);
}

void des_read_b64(t_des *des)
{
    unsigned char buff[32];
    unsigned char buff_des[24];
    unsigned char c;
    int i;

    i = 0;
    if (des->salted && ft_isspace(des->remainder) == 0)
        buff[i++] = des->remainder;
    while ((read(des->fd[0], &c, 1)) > 0)
    {
        if (ft_isspace(c) == 0)
            buff[i++] = c;
        if (i == 32)
            i = manage_block(*des, buff, des->func);
    }
    if (i == 0)
        return;
    b64_decode_buff(buff, i, buff_des);
    des->last = (i == 12);
    des->func(buff_des, des, 8);
    if (i == 24 && ++(des->last))
        des->func(buff_des + 8, des, 8);
}

static void save_remainder(int *count, unsigned char remain[3], uint64_t block)
{
    if (*count == 0)
    {
        remain[0] = (block >> 8) & 0xff;
        remain[1] = block & 0xff;
        *count = 2;
    }
    else if (*count == 1)
        *count = 0;
    else if (*count == 2)
    {
        remain[0] = block & 0xff;
        *count = 1;
    }
}

void des_output_b64(uint64_t block, int len, int fd)
{
    static unsigned char remain[2];
    static int count = 0;
    unsigned char buff[10];
    int max_len;
    int i;

    i = -1;
    max_len = (count) ? 9 : 6;
    while (++i < count)
        buff[i] = remain[i];
    i--;
    while (++i < max_len)
        buff[i] = (block >> 8 * (7 - (i - count))) & 0xff;
    if (len == 8)
        b64_encode(buff, max_len, fd);
    else
    {
        i--;
        while (++i < count + 8)
            buff[i] = (block >> 8 * (7 - (i - count))) & 0xff;
        b64_encode(buff, count + 8, fd);
        ft_putchar_fd('\n', fd);
    }
    save_remainder(&count, remain, block);
}
