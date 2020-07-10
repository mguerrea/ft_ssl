/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_endcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 15:48:27 by mguerrea          #+#    #+#             */
/*   Updated: 2018/12/31 17:08:26 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_endcpy(char *dest, char *src, int n)
{
	int j;

	j = ft_strlen(src) - 1;
	while (n >= 0)
	{
		dest[n] = src[j];
		n--;
		j--;
	}
	return (dest);
}
