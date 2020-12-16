/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa_des.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 13:53:49 by mguerrea          #+#    #+#             */
/*   Updated: 2020/12/16 18:37:35 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"
#include "des.h"
#include "utils.h"

static void get_des_key(t_des *des)
{
    t_pbkdf ctx;
    int i;

    ctx.pass = (unsigned char *)des->pass;
    ctx.keylen = des->key_len;
    ctx.key = des->derived;
    ctx.salt = des->salt;
    ctx.c = 1;
    pbkdf1_md5(&ctx);
    i = -1;
    while (++i < 8)
        des->key = (des->key << 8) | des->derived[i];
    from_buff_to_int(des->salt, &(des->iv), 8);
}

static void encrypt_des(t_des *des, unsigned char *buff, int size)
{
    int i;

    i = 0;
    while (i < size - 7)
    {
        if (size - i == 8)
            des->last = 1;
        des_encrypt_cbc(buff + i, des, 8);
        i += 8;
    }
    if (des->last == 0)
    {
        des->last = 1;
        des_encrypt_cbc(buff + i, des, size - i);
    }
}

void encrypt_key(t_rsa_opt opt, unsigned char *buff, int size)
{
    t_des des;

    des_init(&des, des_encrypt_cbc);
    des.fd[1] = opt.fd[1];
    des.b64 = 1;
    random_string(des.salt, 8);
    des.pass = (opt.pass[1]) ? opt.pass[1] : getpass("Enter PEM pass phrase:");
    get_des_key(&des);
    ft_dprintf(opt.fd[1], PRIV_B);
    ft_dprintf(opt.fd[1], "Proc-Type: 4,ENCRYPTED\nDEK-Info: DES-CBC,");
    print_hex(des.salt, 8, opt.fd[1]);
    ft_dprintf(opt.fd[1], "\n\n");
    encrypt_des(&des, buff, size);
    ft_dprintf(opt.fd[1], PRIV_E);
}