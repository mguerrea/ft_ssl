/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 18:11:20 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/19 18:27:18 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"

int get_key(uint64_t *key, char *str)
{
    uint8_t byte;

    *key = 0;
    if (ft_strlen(str) != 16)
        return (ft_printf("Wrong key size\n"));
    while (*str)
    {
        byte = *(str++);
        if (byte >= '0' && byte <= '9')
            byte = byte - '0';
        else if (byte >= 'a' && byte <= 'f')
            byte = byte - 'a' + 10;
        else if (byte >= 'A' && byte <= 'F')
            byte = byte - 'A' + 10;
        else
            return (ft_printf("Non-hex digit in key\n"));
        *key = (*key << 4) | byte;
    }
    return (0);
}