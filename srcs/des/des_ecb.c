/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 12:53:29 by mguerrea          #+#    #+#             */
/*   Updated: 2020/09/08 13:07:24 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"
#include "utils.h"

void	des_encrypt_ecb(unsigned char buff[8], t_des *des, int len)
{
	uint64_t	block;
	int			i;

	from_buff_to_int(buff, &block, len);
	if (len < 8)
		des_padding(&block, 8 - len);
	des_encrypt_block(&block, des->key);
	i = -1;
	if (des->b64)
		des_output_b64(block, 8, des->fd[1], des);
	else
		print_block(block, des->fd[1]);
}

void	des_decrypt_ecb(unsigned char buff[8], t_des *des, int len)
{
	uint64_t	block;
	int			i;

	from_buff_to_int(buff, &block, len);
	des_decrypt_block(&block, des->key);
	i = -1;
	if (des->last)
		des_remove_padding(&block, &len);
	while (++i < len)
		ft_putchar_fd((block >> 8 * (len - 1 - i)) & 0xff, des->fd[1]);
}

int		ft_des_ecb(int argc, char **argv)
{
	t_des des;

	(void)argc;
	des_init(&des);
	if (des_parse(argv, &des))
		return (0);
	des.func = (des.mode) ? des_decrypt_ecb : des_encrypt_ecb;
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
