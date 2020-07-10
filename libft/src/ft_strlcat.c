/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 15:08:34 by mguerrea          #+#    #+#             */
/*   Updated: 2018/11/25 12:44:15 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t i;
	size_t j;
	size_t len;

	i = 0;
	len = ft_strlen(dest);
	if (size == 0)
		return (ft_strlen(src));
	while (dest[i] != '\0' && i < size)
		i++;
	j = 0;
	while (src[j] != '\0' && i < size - 1)
		dest[i++] = src[j++];
	if (size >= len && size != 0)
		dest[i] = '\0';
	if (size < ft_strlen(dest))
		return (ft_strlen(src) + size);
	return (ft_strlen(src) + len);
}
