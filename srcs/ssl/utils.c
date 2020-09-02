/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 12:49:21 by mguerrea          #+#    #+#             */
/*   Updated: 2020/09/02 13:14:06 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <time.h>
#include <stdlib.h>

void    random_string(unsigned char *str, int len)
{
    int i;

    i = -1;
    srand((unsigned int)time(NULL));
    while (++i < len)
        str[i] = rand();    
}