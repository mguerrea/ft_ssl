/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 16:25:50 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/10 16:28:11 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"
#include "libft.h"

void error_file(char *file)
{
    ft_putstr_fd(file, 2);
    ft_putstr_fd(": No such file or directory\n", 2);
}