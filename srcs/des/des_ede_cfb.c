/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ede_cfb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 00:30:22 by mguerrea          #+#    #+#             */
/*   Updated: 2020/09/08 13:52:06 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"
#include "utils.h"

void	des_encrypt_ede_cfb(unsigned char buff[8], t_des *des, int len)
{
	uint64_t	block;
	uint64_t	k2;
	int			i;

	from_buff_to_int(buff, &block, 8);
	from_buff_to_int(des->derived + 8, &k2, 8);
	des_encrypt_block(&(des->iv), des->key);
	des_decrypt_block(&(des->iv), k2);
	des_encrypt_block(&(des->iv), des->key);
	block = block ^ des->iv;
	des->iv = block;
	i = -1;
	if (des->b64)
		des_output_b64(block, len, des->fd[1], des);
	else
		while (++i < len)
			ft_putchar_fd((block >> 8 * (7 - i)) & 0xff, des->fd[1]);
}

void	des_decrypt_ede_cfb(unsigned char buff[8], t_des *des, int len)
{
	uint64_t	block;
	uint64_t	tmp;
	uint64_t	k2;
	int			i;

	from_buff_to_int(buff, &block, 8);
	from_buff_to_int(des->derived + 8, &k2, 8);
	tmp = block;
	des_encrypt_block(&(des->iv), des->key);
	des_decrypt_block(&(des->iv), k2);
	des_encrypt_block(&(des->iv), des->key);
	block = block ^ des->iv;
	des->iv = tmp;
	i = -1;
	while (++i < len)
		ft_putchar_fd((block >> (56 - 8 * i)) & 0xff, des->fd[1]);
}

int		ft_des_ede_cfb(int argc, char **argv)
{
	t_des des;

	(void)argc;
	des_init(&des, des_decrypt_ede_cfb);
	des.key_len = 128;
	if (des_parse(argv, &des))
		return (0);
	des.func = (des.mode) ? des_decrypt_ede_cfb : des_encrypt_ede_cfb;
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
