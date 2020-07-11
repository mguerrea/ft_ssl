/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 15:39:53 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/11 16:12:33 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef md5_H
# define md5_H

#include "libft.h"
#include "ft_printf.h"
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


typedef struct s_ctx
{
    uint32_t state[4];
    uint32_t count[2];
    unsigned char buffer[64];
}               t_ctx;

typedef enum e_opt
{
    REV = 1 << 0,
    QUIET = 1 << 1,
    INPUT = 1 << 2
}           t_opt;

void md5_transform(uint32_t state[4], unsigned char block[64]);
void md5_encode(unsigned char *output, uint32_t *input, unsigned int len);
void md5_decode(uint32_t *output, unsigned char *input, unsigned int len);
void md5_final (unsigned char digest[16], t_ctx *context);
void md5_update(t_ctx *context, unsigned char *input, uint32_t inputLen);
void md5_init(t_ctx *context);
void md5_op(uint32_t *a, uint32_t to_add, uint32_t s, uint32_t b);
uint32_t md5_f(uint32_t x, uint32_t y, uint32_t z);
uint32_t md5_g(uint32_t x, uint32_t y, uint32_t z);
uint32_t md5_h(uint32_t x, uint32_t y, uint32_t z);
uint32_t md5_i(uint32_t x, uint32_t y, uint32_t z);
void error_file(char *file);
void md5_print(char *format, char *str, unsigned char digest[16], t_opt opt);

#endif