/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 12:26:52 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/19 18:20:49 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DES_H
# define DES_H

#include <stdint.h>
# include "ft_printf.h"
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

void key_schedule(uint64_t key_s[17], uint64_t key);
void initial_perm(uint64_t *block);
void final_perm(uint64_t *block);
void pbox_perm(uint64_t *block);
void expand_block(uint64_t *block);
void des_encrypt_block(uint64_t *block, uint64_t key);
void des_decrypt_block(uint64_t *block, uint64_t key);
int get_key(uint64_t *key, char *str);

#endif