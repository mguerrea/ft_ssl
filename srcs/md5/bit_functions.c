/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 14:48:19 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/10 16:14:22 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

void md5_op(uint32_t *a, uint32_t to_add, uint32_t s, uint32_t b)                       
	{                                                  
		*a += to_add;
		*a = (*a << s) | (*a >> (32 - s));                
		*a += (b);                                    
	}

uint32_t md5_F(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) | (~x & z));
}

uint32_t md5_G(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & z) | (y & ~z));
}

uint32_t md5_H(uint32_t x, uint32_t y, uint32_t z)
{
	return (x ^ y ^ z);
}

uint32_t md5_I(uint32_t x, uint32_t y, uint32_t z)
{
	return (y ^ (x | ~z));
}