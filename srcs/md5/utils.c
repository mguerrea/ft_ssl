/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 15:45:03 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/08 17:39:45 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

void md5_encode(unsigned char *output, uint32_t *input, unsigned int len)
{
    unsigned int i;
    unsigned int j;

    j = 0;
    i = 0;
    while (j < len)
    {
        output[j] = (unsigned char)(input[i] & 0xff);
        output[j + 1] = (unsigned char)((input[i] >> 8) & 0xff);
        output[j + 2] = (unsigned char)((input[i] >> 16) & 0xff);
        output[j + 3] = (unsigned char)((input[i] >> 24) & 0xff);
        i++;
        j += 4;
    }
}

void md5_decode(uint32_t *output, unsigned char *input, unsigned int len)
{
    unsigned int i;
    unsigned int j;

    j = 0;
    i = 0;
    while (j < len)
    {
        output[i] = ((UINT4)input[j]) | (((UINT4)input[j+1]) << 8) |
   (((UINT4)input[j+2]) << 16) | (((UINT4)input[j+3]) << 24);
        i++;
        j += 4;
    }
}