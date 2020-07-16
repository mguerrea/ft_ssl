/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 19:37:25 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/16 23:54:19 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "ft_printf.h"
#include "base64.h"

const char *g_base = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
int g_count = 0;

static void b64_read(int fd_in, int fd_out, void (*func)(unsigned char *, unsigned int, int))
{
    unsigned char buff[3 * 512];
    int ret;

    if (fd_out < 0 || fd_in < 0)
        return ;
    while ((ret = read(fd_in, buff, 3 * 512)) > 0)
    {
        func(buff, ret, fd_out);
    }
    ft_putchar_fd('\n', fd_out);
}

int		ft_base64(int argc, char **argv)
{
    int i;
    void (*func)(unsigned char *, unsigned int, int);
    int fd_out;
    int fd_in;

    i = 1;
    func = b64_encode;
    fd_out = STDOUT_FILENO;
    fd_in = STDIN_FILENO;
    while (i < argc)
    {
        if (ft_strcmp(argv[i], "-d") == 0)
            func = b64_decode;
        if (ft_strcmp(argv[i], "-o") == 0 && argv[i + 1])
            if ((fd_out = open(argv[i + 1], O_WRONLY|O_CREAT, 0666)) == -1)
                ft_printf("ft_ssl: base64: %s: No such file or directory\n", argv[i + 1]);
        if (ft_strcmp(argv[i], "-i") == 0 && argv[i + 1])
            if ((fd_in = open(argv[i + 1], O_RDONLY)) == -1)
                ft_printf("ft_ssl: base64: %s: No such file or directory\n", argv[i + 1]);
    i++;
    }
    b64_read(fd_in, fd_out, func);
    return(0);
}