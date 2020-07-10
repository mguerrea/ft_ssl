/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 15:14:36 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/10 14:35:38 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "md5.h"
#include <stdlib.h>
#include <unistd.h>
#define BUFFSIZE 2048

int main (int argc, char **argv)
{
    md5_dispatch(argc, argv);
}