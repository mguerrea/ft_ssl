/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 11:54:50 by mguerrea          #+#    #+#             */
/*   Updated: 2020/12/11 13:33:58 by mguerrea         ###   ########.fr       */
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

uint64_t randint64(uint64_t min, uint64_t max);
uint64_t pow_mod(uint64_t x, uint64_t n, uint64_t mod);

int miller_rabin64(uint64_t n);
int miller_rabin(uint64_t n, float p);

#endif