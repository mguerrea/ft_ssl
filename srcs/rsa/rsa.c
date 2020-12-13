/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 14:22:27 by mguerrea          #+#    #+#             */
/*   Updated: 2020/12/13 17:35:37 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rsa.h"
#include "base64.h"

int read_key(t_rsa_priv *key, t_rsa_opt opt)
{
    unsigned char buff[40];
    unsigned char buff2[3072];
    char *header;
    int i;

    i = 0;
    if (opt.format[0] == DER)
        read(opt.fd[0], buff2, 3072);
    else
    {
        header = (opt.pubin) ? PUB_B : PRIV_B;
        read(opt.fd[0], buff, ft_strlen(header));
        if (ft_strncmp((char *)buff, header, ft_strlen(header)) != 0)
            return (ft_dprintf(2, "unable to load key\n"));
        while (!ft_strchr((char *)buff, '=') && (read(opt.fd[0], buff, 4)) >= 0 && ft_strncmp((char *)buff, "----", 4))
        {
            b64_decode_buff(buff, 4, &(buff2[i]));
            i += 3;
            if (i % 48 == 0)
                read(opt.fd[0], buff + 4, 1);
        }
    }
    return ((opt.pubin) ? asn1_decode_pubkey(key, buff2) : asn1_decode_privkey(key, buff2));
}

int ft_rsa(int argc, char **argv)
{
    t_rsa_opt opt;
    t_rsa_priv key;

    ft_memset(&key, 0, sizeof(t_rsa_priv));
    ft_memset(&opt, 0, sizeof(t_rsa_opt));
    rsa_parsing(&opt, argc, argv);
    if (read_key(&key, opt))
        return (-1);
    if (opt.text == 1)
        print_infos(opt, key);
    if (opt.noout != 1)
    {
        ft_dprintf(2, "writing RSA key\n");
        if (opt.pubin == 0 && opt.pubout == 0)
            format_privkey(key, opt.fd[1], opt.format[1]);
        else
            format_pubkey(key, opt.fd[1], opt.format[1]);
    }
    return (0);
}