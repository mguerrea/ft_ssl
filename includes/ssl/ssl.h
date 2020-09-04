/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 11:56:53 by mguerrea          #+#    #+#             */
/*   Updated: 2020/09/04 23:14:17 by mguerrea         ###   ########.fr       */
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

const t_cmd g_commands[] =
{
	{"md5", ft_md5},
	{"sha256", ft_sha256},
	{"sha224", ft_sha224},
	{"base64", ft_base64},
	{"des-ecb", ft_des_ecb},
	{"des-cbc", ft_des_cbc},
	{NULL, NULL}
};

#endif
