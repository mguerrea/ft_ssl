/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 18:11:20 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/20 18:33:53 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"

int get_key(uint64_t *key, char *str)
{
    uint8_t byte;

    *key = 0;
    if (ft_strlen(str) != 16)
        return (ft_printf("Wrong key size\n"));
    while (*str)
    {
        byte = *(str++);
        if (byte >= '0' && byte <= '9')
            byte = byte - '0';
        else if (byte >= 'a' && byte <= 'f')
            byte = byte - 'a' + 10;
        else if (byte >= 'A' && byte <= 'F')
            byte = byte - 'A' + 10;
        else
            return (ft_printf("Non-hex digit in key\n"));
        *key = (*key << 4) | byte;
    }
    return (0);
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
