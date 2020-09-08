/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ede3_ecb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 22:26:13 by mguerrea          #+#    #+#             */
/*   Updated: 2020/09/08 13:09:43 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"
#include "utils.h"

void	des_encrypt_ede3_ecb(unsigned char buff[8], t_des *des, int len)
{
	uint64_t	block;
	uint64_t	k[2];

	from_buff_to_int(des->derived + 8, &(k[0]), 8);
	from_buff_to_int(des->derived + 16, &(k[1]), 8);
	from_buff_to_int(buff, &block, len);
	if (len < 8)
		des_padding(&block, 8 - len);
	des_encrypt_block(&block, des->key);
	des_decrypt_block(&block, k[0]);
	des_encrypt_block(&block, k[1]);
	if (des->b64)
		des_output_b64(block, 8, des->fd[1], des);
	else
		print_block(block, des->fd[1]);
}

void	des_decrypt_ede3_ecb(unsigned char buff[8], t_des *des, int len)
{
	uint64_t	block;
	uint64_t	k[2];

	from_buff_to_int(buff, &block, len);
	from_buff_to_int(des->derived + 8, &(k[0]), 8);
	from_buff_to_int(des->derived + 16, &(k[1]), 8);
	des_decrypt_block(&block, k[1]);
	des_encrypt_block(&block, k[0]);
	des_decrypt_block(&block, des->key);
	if (des->last)
		des_remove_padding(&block, &len);
	while (len--)
		ft_putchar_fd((block >> 8 * len) & 0xff, des->fd[1]);
}

int		ft_des_ede3_ecb(int argc, char **argv)
{
	t_des des;

	(void)argc;
	des_init(&des);
	des.key_len = 192;
	if (des_parse(argv, &des))
		return (0);
	des.func = (des.mode) ? des_decrypt_ede3_ecb : des_encrypt_ede3_ecb;
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
