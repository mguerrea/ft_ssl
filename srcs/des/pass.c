/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 21:24:42 by mguerrea          #+#    #+#             */
/*   Updated: 2020/09/04 23:09:34 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"
#include "sha.h"
#include <stdio.h>

const char *g_salt = "Salted__";

int get_salt(t_des *des, char *str)
{
    int i;
    uint8_t byte;

    i = -1;
    if (ft_strlen(str) < 16)
        ft_printf("salt is too short, padding with zero bytes to length\n");
    while (str[++i])
    {
        byte = str[i];
        if (i % 2 == 1)
            des->salt[i / 2] = des->salt[i / 2] << 4;
        if (byte >= '0' && byte <= '9')
            byte = byte - '0';
        else if (byte >= 'a' && byte <= 'f')
            byte = byte - 'a' + 10;
        else if (byte >= 'A' && byte <= 'F')
            byte = byte - 'A' + 10;
        else
            return (ft_printf("Non-hex digit in salt\n"));
        des->salt[i / 2] |= byte;
    }  
    des->salted = 1;
    return (0);
}

void print_salt(t_des *des)
{
    uint64_t block;
    int i;

    block = 0;
    i = -1;
    if (des->mode == 0 && des->b64 == 0)
    {
        write(des->fd[1], g_salt, 8);
        write(des->fd[1], des->salt, 8);
    }
    else if (des->mode == 0 && des->b64 == 1)
    {
        while (++i < 8)
            block = (block << 8) | g_salt[i];
        des_output_b64(block, 8, des->fd[1]);
        i = -1;
        while (++i < 8)
            block = (block << 8) | des->salt[i];
        des_output_b64(block, 8, des->fd[1]);
    }
}

int read_salt(t_des *des)
{
    unsigned char buff[32];
    unsigned char salt[24];

    if (des->mode == 1 && des->b64 == 0)
    {
        if (read(des->fd[0], buff, 16) < 16 || ft_memcmp(buff, "Salted__", 8))
            return(ft_printf("Missing salt\n"));
        ft_memcpy(des->salt, buff + 8, 8);
    }
    else if (des->mode == 1 && des->b64 == 1)
    {
        if (read(des->fd[0], buff, 32) < 32)
            return(ft_printf("Missing salt\n"));
        b64_decode_buff(buff, 32, salt);
        if (ft_memcmp(salt, g_salt, 8) != 0)
            return(ft_printf("Missing salt\n"));
        ft_memcpy(des->salt, salt + 8, 8);
        while ((read(des->fd[0], &(des->remainder), 1)) > 0 && ft_isspace(des->remainder));
        if (ft_isspace(des->remainder))
            des->last = 1;
        ft_memcpy(des->block, salt + 16, 8);
    }
    return (0);
}

int get_pass(t_des *des)
{
    unsigned char key[8];
    int i;

    i = -1;
    if (des->salted == 0 && des->mode == 0)
        random_string(des->salt, 8);
    if (read_salt(des) != 0)
        return (1);
    print_salt(des);
    des->salted = 1;
    pbkdf2((unsigned char *)des->pass, des->salt, 100, 64, key);
    while (++i < 8)
        des->key = (des->key << 8) | key[i];
    if (des->mode == 1 && des->b64 == 1)
        des->func(des->block, des, 8);
    return (0);
}