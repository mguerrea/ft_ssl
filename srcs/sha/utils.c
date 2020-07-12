/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 11:52:07 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/12 11:54:29 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha.h"

void	sha256_print(char *format, char *str, unsigned char digest[16], t_opt opt)
{
	int i;

	i = 0;
	if (!(opt & REV) && !(opt & QUIET))
		ft_printf(format, str);
	while (i < 16)
	{
		ft_printf("%02x", digest[i]);
		i++;
	}
	if (opt & REV && ft_strcmp(format, "SHA256 (\"%s\") = ") == 0
		&& !(opt & QUIET))
		ft_printf(" \"%s\"", str);
	else if (opt & REV && !(opt & QUIET))
		ft_printf(" %s", str);
	ft_printf("\n");
}