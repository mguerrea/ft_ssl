/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 17:51:46 by mguerrea          #+#    #+#             */
/*   Updated: 2020/09/02 13:14:13 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdint.h>

typedef enum	e_opt
{
	REV = 1 << 0,
	QUIET = 1 << 1,
	INPUT = 1 << 2
}				t_opt;

unsigned int g_hash_size;

uint32_t	rot_l(uint32_t a, int b);
uint32_t	rot_r(uint32_t a, int b);
void		digest_print(char *fmt, char *str, unsigned char *dgst, t_opt opt);
void		pbkdf2(unsigned char *pass, unsigned char *salt, int c, int dkLen, unsigned char *DK);
void   		random_string(unsigned char *str, int len);

#endif
