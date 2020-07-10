/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 15:38:01 by mguerrea          #+#    #+#             */
/*   Updated: 2018/11/05 16:46:13 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*dest2;
	char	*src2;

	i = 0;
	src2 = (char *)src;
	dest2 = (char *)dest;
	if (src > dest)
		while (i < n)
		{
			dest2[i] = src2[i];
			i++;
		}
	else
		while (n > 0)
		{
			dest2[n - 1] = src2[n - 1];
			n--;
		}
	return (dest);
}
