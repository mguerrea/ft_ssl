/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 17:04:52 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/19 18:43:34 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"
#include <unistd.h>
#include <stdlib.h>
#include <crypt.h>
#include "ft_printf.h"

static void padding(uint64_t *block, uint8_t len)
{
    int i;

    i = 0;
    while (i < len)
    {
        *block = *block << 8 | len;
        i++;
    }
}

void des_encrypt_ecb(unsigned char buff[8], uint64_t key, int len, int fd)
{
    uint64_t block;
    int i;

    block = 0;
    i = -1;
    while (++i < len)
        block = block << 8 | buff[i];
    if (len < 8)
        padding(&block, 8 - len);
    des_encrypt_block(&block, key);
    i = -1;
    while (++i < 8)
        ft_putchar_fd((block >> 8 * (7 - i)) & 0xff, fd);
}

void des_decrypt_ecb(unsigned char buff[8], uint64_t key, int len, int fd)
{
    uint64_t block;
    int i;
    int pad;

    block = 0;
    i = -1;
    if (len == 0)
        return ;
    while (++i < len)
        block = block << 8 | buff[i];
    des_decrypt_block(&block, key);
    i = -1;
    if ((pad = block & 0xff) <= 8)
    {
        while(++i < 8 - pad)
            ft_putchar_fd((block >> 8 * (7 - i)) & 0xff, fd);
    }
    else
        while(++i < 8)
            ft_putchar_fd((block >> 8 * (7 - i)) & 0xff, fd);
}

void         des_ecb_read(int fd[2], uint64_t key,
    void	(*func)(unsigned char *, uint64_t, int, int))
{
    unsigned char buff[8];
    int ret;

    if (fd[0] == -1 || fd[1] == -1)
        return ;
    while ((ret = read(fd[0], buff, 8)) > 0)
	{
        if (ret == 8)
        {
            func(buff, key, ret, fd[1]);
        }
        else
            break ;
	}
    func(buff, key, ret, fd[1]);
}

int        des_parse(char **argv, int *fd, uint64_t *key,
 void	(**func)(unsigned char *, uint64_t, int, int))
{
    int i;

    i = 0;
    while (argv[++i])
    {
        if (ft_strcmp(argv[i], "-d") == 0)
			*func = des_decrypt_ecb;
        if (ft_strcmp(argv[i], "-k") == 0 && argv[i + 1])
            if (get_key(key, argv[i + 1]) != 0)
                return (1);
		if (ft_strcmp(argv[i], "-o") == 0 && argv[i + 1])
			if ((fd[1] = open(argv[i + 1], O_WRONLY | O_CREAT, 0666)) == -1)
				return (ft_printf("ft_ssl: des-ecb: %s: No such file or directory\n",
					argv[i + 1]));
		if (ft_strcmp(argv[i], "-i") == 0 && argv[i + 1])
			if ((fd[0] = open(argv[i + 1], O_RDONLY)) == -1)
				return (ft_printf("ft_ssl: des-ecb: %s: No such file or directory\n",
					argv[i + 1]));
    }
    return (0);
}

int			ft_des_ecb(int argc, char **argv)
{
	// int		i;
	void	(*func)(unsigned char *, uint64_t, int, int);
    int fd[2];
    uint64_t key;

    (void)argc;
	func = des_encrypt_ecb;
    fd[0] = STDIN_FILENO;
    fd[1] = STDOUT_FILENO;
    key = 0;
    if (des_parse(argv, fd, &key, &func))
        return (0);
	des_ecb_read(fd, key, func);
    if (fd[0] > 2)
        close(fd[0]);
    if (fd[1] > 2)
        close(fd[1]);
	return (0);
}
