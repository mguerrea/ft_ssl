/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 11:52:52 by mguerrea          #+#    #+#             */
/*   Updated: 2020/09/08 13:11:19 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"
#include "sha.h"

const char *g_error_size = "hex string is too short, padding with zero bytes \
to length\n";

int			get_hex(uint64_t *nb, char *str)
{
	uint8_t	byte;
	int		i;

	i = -1;
	if (ft_strlen(str) < 16)
		ft_putstr_fd(g_error_size, 2);
	while (str[++i])
	{
		byte = str[i];
		if (byte >= '0' && byte <= '9')
			byte = byte - '0';
		else if (byte >= 'a' && byte <= 'f')
			byte = byte - 'a' + 10;
		else if (byte >= 'A' && byte <= 'F')
			byte = byte - 'A' + 10;
		else
			return (ft_printf("Non-hex digit in string\n"));
		*nb = (*nb << 4) | byte;
	}
	while (i++ < 16)
		*nb = *nb << 4;
	return (0);
}

int			get_key(t_des *des, char *str)
{
	int		i;
	uint8_t	byte;

	if (ft_strlen(str) < (unsigned int)des->key_len / 4)
		ft_putstr_fd(g_error_size, 2);
	i = -1;
	while (str[++i])
	{
		byte = str[i];
		if (i % 2 == 1)
			des->derived[i / 2] = des->derived[i / 2] << 4;
		if (byte >= '0' && byte <= '9')
			byte = byte - '0';
		else if (byte >= 'a' && byte <= 'f')
			byte = byte - 'a' + 10;
		else if (byte >= 'A' && byte <= 'F')
			byte = byte - 'A' + 10;
		else
			return (ft_printf("Non-hex digit in key\n"));
		des->derived[i / 2] |= byte;
	}
	from_buff_to_int(des->derived, &(des->key), 8);
	return (0);
}

static int	des_parse2(char **argv, t_des *des, int i)
{
	if (ft_strcmp(argv[i], "-d") == 0)
		des->mode = 1;
	if (ft_strcmp(argv[i], "-a") == 0)
		des->b64 = 1;
	if (ft_strcmp(argv[i], "-v") == 0 && argv[i + 1])
		if (get_hex(&(des->iv), argv[i + 1]) != 0)
			return (1);
	if (ft_strcmp(argv[i], "-s") == 0 && argv[i + 1])
		if (get_salt(des, argv[i + 1]) != 0)
			return (1);
	if (ft_strcmp(argv[i], "-o") == 0 && argv[i + 1])
		if ((des->fd[1] = open(argv[i + 1], 01101, 0666)) == -1)
			return (error_file(argv[i + 1]));
	if (ft_strcmp(argv[i], "-i") == 0 && argv[i + 1])
		if ((des->fd[0] = open(argv[i + 1], O_RDONLY)) == -1)
			return (error_file(argv[i + 1]));
	return (0);
}

int			des_parse(char **argv, t_des *des)
{
	int i;
	int key;

	i = 0;
	key = 0;
	while (argv[++i])
	{
		if (des_parse2(argv, des, i))
			return (1);
		if (ft_strcmp(argv[i], "-k") == 0 && argv[i + 1])
		{
			if (get_key(des, argv[i + 1]) != 0)
				return (1);
			key = 1;
		}
		if (ft_strcmp(argv[i], "-p") == 0 && argv[i + 1])
			des->pass = argv[i + 1];
	}
	return (key == 0 ? key_from_pass(des) : 0);
}
