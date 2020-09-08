/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ofb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 16:37:11 by mguerrea          #+#    #+#             */
/*   Updated: 2020/09/08 13:54:48 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"
#include "utils.h"

void	des_encrypt_ofb(unsigned char buff[8], t_des *des, int len)
{
	uint64_t	block;
	int			i;

	from_buff_to_int(buff, &block, 8);
	des_encrypt_block(&(des->iv), des->key);
	block = block ^ des->iv;
	i = -1;
	if (des->b64)
		des_output_b64(block, len, des->fd[1], des);
	else
		while (++i < len)
			ft_putchar_fd((block >> 8 * (7 - i)) & 0xff, des->fd[1]);
}

void	des_decrypt_ofb(unsigned char buff[8], t_des *des, int len)
{
	uint64_t	block;
	int			i;

	from_buff_to_int(buff, &block, 8);
	des_encrypt_block(&(des->iv), des->key);
	block = block ^ des->iv;
	i = -1;
	while (++i < len)
		ft_putchar_fd((block >> (56 - 8 * i)) & 0xff, des->fd[1]);
}

int		ft_des_ofb(int argc, char **argv)
{
	t_des des;

	(void)argc;
	des_init(&des, des_decrypt_ofb);
	if (des_parse(argv, &des))
		return (0);
	des.func = (des.mode) ? des_decrypt_ofb : des_encrypt_ofb;
	if (des.b64 && des.mode)
		des_read_b64(&des);
	else
		des_read(&des);
	if (des.fd[0] > 2)
		close(des.fd[0]);
	if (des.fd[1] > 2)
		close(des.fd[1]);
	return (0);
}
