/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 11:54:50 by mguerrea          #+#    #+#             */
/*   Updated: 2020/12/11 17:48:37 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RSA_H
# define RSA_H

# include <stdint.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include "libft.h"
# include "ft_printf.h"

typedef struct s_rsa_priv {
    uint64_t n;
    uint64_t e;
    uint64_t d;
    uint64_t p;
    uint64_t q;
    uint64_t pq;
    uint64_t dq;
    uint64_t qinv;
}               t_rsa_priv;

uint64_t randint64(uint64_t min, uint64_t max);
uint64_t pow_mod(uint64_t x, uint64_t n, uint64_t mod);

int miller_rabin64(uint64_t n);
int miller_rabin(uint64_t n, float p);
uint64_t get_prime(int size);

int asn1_size_int(uint64_t nb);
void asn1_encode_int(unsigned char *buff, uint64_t nb);

#endif