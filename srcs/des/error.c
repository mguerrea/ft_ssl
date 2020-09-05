/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 13:21:22 by mguerrea          #+#    #+#             */
/*   Updated: 2020/09/05 13:26:56 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"
#include "libft.h"

int error_file(char *file)
{
    ft_putstr_fd("ft_ssl: des: ", 2);
    ft_putstr_fd(file, 2);
    ft_putstr_fd(": No such file or directory\n", 2);
    return (1);
}