/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 17:51:46 by mguerrea          #+#    #+#             */
/*   Updated: 2020/12/16 18:25:48 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdint.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>

typedef enum	e_opt
{
	REV = 1 << 0,
	QUIET = 1 << 1,
	INPUT = 1 << 2
}				t_opt;

typedef struct	s_pbkdf
{
	unsigned char	*pass;
	unsigned char	*salt;
	int				c;
	int				keylen;
	unsigned char	*key;
}				t_pbkdf;

unsigned int	g_hash_size;

uint32_t		rot_l(uint32_t a, int b);
uint32_t		rot_r(uint32_t a, int b);
void			digest_print(char *fmt, char *str, unsigned char *dgst,
	t_opt opt);
void			pbkdf2(t_pbkdf *ctx);
void			random_string(unsigned char *str, int len);
void			print_block(uint64_t block, int fd);
void			from_buff_to_int(unsigned char *buff, uint64_t *nb, int len);
int				error_file(char *file, char *cmd);
void			pbkdf1_md5(t_pbkdf *ctx);
void			pbkdf1_sha256(t_pbkdf *ctx);
void			print_hex(unsigned char *str, int len, int fd);

#endif
