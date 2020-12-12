/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 12:19:41 by mguerrea          #+#    #+#             */
/*   Updated: 2020/12/12 15:01:38 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE64_H
# define BASE64_H

# include <stdint.h>
# include "ft_printf.h"
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

void	b64_encode(unsigned char *str, unsigned int len, int fd);
void	b64_decode(unsigned char *str, unsigned int len, int fd);
void	b64_decode_buff(unsigned char *str, unsigned int len,
	unsigned char *output);

#endif
