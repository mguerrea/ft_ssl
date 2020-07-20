/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 17:04:52 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/20 20:04:50 by mguerrea         ###   ########.fr       */
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
		if (ft_strcmp(argv[i], "-o") == 0 && argv[i + 1])
			if ((des->fd[1] = open(argv[i + 1], O_WRONLY | O_CREAT, 0666)) == -1)
				return (ft_printf("ft_ssl: des-ecb: %s: No such file or directory\n",
					argv[i + 1]));
		if (ft_strcmp(argv[i], "-i") == 0 && argv[i + 1])
			if ((des->fd[0] = open(argv[i + 1], O_RDONLY)) == -1)
				return (ft_printf("ft_ssl: des-ecb: %s: No such file or directory\n",
					argv[i + 1]));
    }
    return (0);
}

void    des_read_b64(t_des des,
    void	(*func)(unsigned char *, t_des, int))
{
    unsigned char buff[32];
    unsigned char buff_des[24];
    unsigned char c;
    int i;

    i = 0;
    if (des.fd[0] == -1 || des.fd[1] == -1)
        return ;
    while ((read(des.fd[0], &c, 1)) > 0)
    {
        if (ft_isspace(c) == 0)
        {
            buff[i] = c;
            i++;
        }
        if (i == 32)
        {
            for (int j = 0; j < 12; j++)
            b64_decode_buff(buff, 32, buff_des);
            i = 0;
            func(buff_des, des, 8);
            func(buff_des + 8, des, 8);
            func(buff_des + 16, des, 8);
        }
    }
    if (i)
    {
    b64_decode_buff(buff, i, buff_des);
    func(buff_des, des, 8);
    if (i == 18)
        func(buff_des + 8, des, 8);
    }
}

void         des_read(t_des des,
    void	(*func)(unsigned char *, t_des, int))
{
    unsigned char buff[8];
    int ret;

    if (des.fd[0] == -1 || des.fd[1] == -1)
        return ;
    while ((ret = read(des.fd[0], buff, 8)) > 0)
	{
        if (ret == 8)
            func(buff, des, ret);
        else
            break ;
	}
    if (des.mode == 0)
        func(buff, des, ret);
}

