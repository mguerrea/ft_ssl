/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/16 11:58:44 by gmichaud          #+#    #+#             */
/*   Updated: 2016/11/10 17:17:11 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*dest;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(dest = ft_strnew(sizeof(*dest) * (len1 + len2))))
		return (NULL);
	len1 = 0;
	while (s1[len1])
	{
		dest[len1] = s1[len1];
		len1++;
	}
	len2 = 0;
	while (s2[len2])
	{
		dest[len1] = s2[len2];
		len1++;
		len2++;
	}
	return (dest);
}
