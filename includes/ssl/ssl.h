/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 11:56:53 by mguerrea          #+#    #+#             */
/*   Updated: 2020/09/08 12:55:06 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_H
# define SSL_H

# include "ft_printf.h"

typedef struct	s_cmd
{
	char	*command;
	int		(*algo)(int argc, char **argv);
}				t_cmd;

int				ft_md5 (int argc, char **argv);
int				ft_sha256 (int argc, char **argv);
int				ft_sha224(int argc, char **argv);
int				ft_base64(int argc, char **argv);
int				ft_des_ecb(int argc, char **argv);
int				ft_des_cbc(int argc, char **argv);
int				ft_des_cfb(int argc, char **argv);
int				ft_des_ofb(int argc, char **argv);
int				ft_des_ede_ecb(int argc, char **argv);
int				ft_des_ede_cbc(int argc, char **argv);
int				ft_des_ede_cfb(int argc, char **argv);
int				ft_des_ede_ofb(int argc, char **argv);
int				ft_des_ede3_ecb(int argc, char **argv);
int				ft_des_ede3_cbc(int argc, char **argv);
int				ft_des_ede3_cfb(int argc, char **argv);
int				ft_des_ede3_ofb(int argc, char **argv);

const t_cmd g_commands[] =
{
	{"md5", ft_md5},
	{"sha256", ft_sha256},
	{"sha224", ft_sha224},
	{"base64", ft_base64},
	{"des-ecb", ft_des_ecb},
	{"des-cbc", ft_des_cbc},
	{"des", ft_des_cbc},
	{"des-cfb", ft_des_cfb},
	{"des-ofb", ft_des_ofb},
	{"des-ede-ecb", ft_des_ede_ecb},
	{"des-ede-cbc", ft_des_ede_cbc},
	{"des-ede", ft_des_ede_ecb},
	{"des-ede-cfb", ft_des_ede_cfb},
	{"des-ede-ofb", ft_des_ede_ofb},
	{"des-ede3-ecb", ft_des_ede3_ecb},
	{"des-ede3-cbc", ft_des_ede3_cbc},
	{"des-ede3", ft_des_ede3_ecb},
	{"des3", ft_des_ede3_cbc},
	{"des-ede3-cfb", ft_des_ede3_cfb},
	{"des-ede3-ofb", ft_des_ede3_ofb},
	{NULL, NULL}
};

#endif
