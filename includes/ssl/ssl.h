/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 11:56:53 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/11 12:06:21 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_H
#define SSL_H

typedef struct s_cmd
{
	char *command;
	int (*algo)(int argc, char **argv);
} t_cmd;

const t_cmd g_commands[] =
{
	{"md5", ft_md5},
	{NULL, NULL}
};

#endif