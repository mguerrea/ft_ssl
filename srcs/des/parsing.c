/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 11:52:52 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/22 13:52:10 by mguerrea         ###   ########.fr       */
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

int         get_pass(uint64_t *key, char *pass)
{
    // unsigned char out[32];
    // char *test = "test";

    (void)key;
    (void)pass;
    // hmac_sha256((unsigned char*)pass, ft_strlen(pass), (unsigned char *)test, ft_strlen(test), out, 32);
    // for (int i = 0; i < 32; i++)
    //     ft_printf("%02x", out[i]);
    // ft_printf("\n");
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
            if (get_pass(&(des->key), argv[i + 1]) != 0)
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
