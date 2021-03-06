/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 12:26:52 by mguerrea          #+#    #+#             */
/*   Updated: 2020/09/08 13:57:44 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DES_H
# define DES_H

# include <stdint.h>
# include "ft_printf.h"
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct	s_des
{
	uint64_t		key;
	int				fd[2];
	uint64_t		iv;
	int				mode;
	int				b64;
	int				last;
	int				salted;
	char			*pass;
	unsigned char	salt[8];
	unsigned char	remainder;
	unsigned char	block[8];
	unsigned char	derived[32];
	int				key_len;
	void			(*func)(unsigned char *, struct s_des *, int);
}				t_des;

/*
** BLOCK ENCRYPTION
*/

void			key_schedule(uint64_t key_s[17], uint64_t key);
void			initial_perm(uint64_t *block);
void			final_perm(uint64_t *block);
void			pbox_perm(uint64_t *block);
void			expand_block(uint64_t *block);
void			des_encrypt_block(uint64_t *block, uint64_t key);
void			des_decrypt_block(uint64_t *block, uint64_t key);

/*
** PARSING & UTILS
*/

void			des_padding(uint64_t *block, uint8_t len);
void			des_read(t_des *des);
int				des_parse(char **argv, t_des *des);
void			b64_decode_buff(unsigned char *str, unsigned int len,
	unsigned char *output);
void			des_read_b64(t_des *des);
void			b64_encode(unsigned char *str, unsigned int len, int fd);
void			des_output_b64(uint64_t block, int len, int fd, t_des *des);
int				des_parse(char **argv, t_des *des);
void			des_remove_padding(uint64_t *block, int *len);
void			des_init(t_des *des,
	void (*func)(unsigned char *, struct s_des *, int));
int				key_from_pass(t_des *des, char *pass);
int				get_salt(t_des *des, char *str);
int				error_file(char *file);

#endif
