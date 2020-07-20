/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 12:53:29 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/20 20:05:22 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"

void des_encrypt_ecb(unsigned char buff[8], t_des des, int len)
{
    uint64_t block;
    int i;

    block = 0;
    i = -1;
    while (++i < len)
        block = block << 8 | buff[i];
    if (len < 8)
        des_padding(&block, 8 - len);
    des_encrypt_block(&block, des.key);
    i = -1;
    if (des.b64)
        des_output_b64(block, len, des.fd[1]);
    else
        while (++i < 8)
            ft_putchar_fd((block >> 8 * (7 - i)) & 0xff, des.fd[1]);
}

void des_decrypt_ecb(unsigned char buff[8], t_des des, int len)
{
    uint64_t block;
    int i;
    int pad;

    block = 0;
    i = -1;
    while (++i < len)
        block = block << 8 | buff[i];
    des_decrypt_block(&block, des.key);
    i = -1;
    if ((pad = block & 0xff) <= 8)
    {
        while(++i < 8 - pad)
            ft_putchar_fd((block >> 8 * (7 - i)) & 0xff, des.fd[1]);
    }
    else
        while(++i < 8)
            ft_putchar_fd((block >> 8 * (7 - i)) & 0xff, des.fd[1]);
}

int			ft_des_ecb(int argc, char **argv)
{
    t_des des;

    (void)argc;
    des.mode = 0;
    des.fd[0] = STDIN_FILENO;
    des.fd[1] = STDOUT_FILENO;
    des.b64 = 0;
    if (des_parse(argv, &des))
        return (0);
    if (des.b64 && des.mode)
        des_read_b64(des, des_decrypt_ecb);
    else
	    des_read(des, (des.mode) ? des_decrypt_ecb : des_encrypt_ecb);
    if (des.fd[0] > 2)
        close(des.fd[0]);
    if (des.fd[1] > 2)
        close(des.fd[1]);
	return (0);
}
