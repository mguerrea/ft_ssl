/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 11:52:52 by mguerrea          #+#    #+#             */
/*   Updated: 2020/09/02 13:39:06 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"
#include "sha.h"
#include <stdio.h>

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

int get_salt(t_des *des, char *str)
{
    int i;
    uint8_t byte;

    i = -1;
    if (ft_strlen(str) != 16)
        return (ft_printf("Wrong salt size\n"));
    while (++i < 16)
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



int get_pass(t_des *des)
{
    unsigned char buff[16];
    unsigned char key[8];
    int i;

    i = -1;
    printf("pass = %s\n", des->pass);
    printf("salted = %d\n", des->salted);
    if (des->salted == 0 && des->mode == 0)
        random_string(des->salt, 8);
    else if (des->mode == 1)
    {
        if (read(des->fd[0], buff, 16) < 16 || ft_memcmp(buff, "Salted__", 8))
            return(ft_printf("Missing salt\n"));
        memcpy(des->salt, buff + 8, 8);
    }
    if (des->mode == 0)
    {
        write(des->fd[1], "Salted__", 8);
        write(des->fd[1], des->salt, 8);
    }
    des->salted = 1;
    pbkdf2((unsigned char *)des->pass, des->salt, 100, 64, key);
    while (++i < 8)
        des->key = (des->key << 8) | key[i];
    for (int j = 0; j < 8; j++)
        printf("%02X", des->salt[j]);
    printf("\n");
    for (int j = 0; j < 8; j++)
        printf("%02X", key[j]);
    return (0);
}

int        des_parse(char **argv, t_des *des)
{
    int i;

    i = 0;
    while (argv[++i])
    {
        if (ft_strcmp(argv[i], "-d") == 0)
			des->mode = 1;
        if (ft_strcmp(argv[i], "-a") == 0)
			des->b64 = 1;
        if (ft_strcmp(argv[i], "-k") == 0 && argv[i + 1])
            if (get_key(&(des->key), argv[i + 1]) != 0)
                return (1);
        if (ft_strcmp(argv[i], "-p") == 0 && argv[i + 1])
            des->pass = argv[i + 1];
        if (ft_strcmp(argv[i], "-s") == 0 && argv[i + 1])
            if (get_salt(des, argv[i + 1]) != 0)
                return (1);
		if (ft_strcmp(argv[i], "-o") == 0 && argv[i + 1])
			if ((des->fd[1] = open(argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
				return (ft_printf("ft_ssl: des-ecb: %s: No such file or directory\n",
					argv[i + 1]));
		if (ft_strcmp(argv[i], "-i") == 0 && argv[i + 1])
			if ((des->fd[0] = open(argv[i + 1], O_RDONLY)) == -1)
				return (ft_printf("ft_ssl: des-ecb: %s: No such file or directory\n",
					argv[i + 1]));
    }
    return (des->pass ? get_pass(des) : 0);
}
