/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 13:52:44 by mguerrea          #+#    #+#             */
/*   Updated: 2018/12/18 13:53:17 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_nbrlen(int nb)
{
	int count;

	count = 0;
	if (nb == 0)
		count++;
	while (nb > 0)
	{
		count++;
		nb = nb / 10;
	}
	return (count);
}
