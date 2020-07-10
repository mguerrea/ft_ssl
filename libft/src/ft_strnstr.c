/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 14:55:35 by mguerrea          #+#    #+#             */
/*   Updated: 2018/11/17 13:21:35 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	k;

	if (*s2 == '\0')
		return ((char *)s1);
	i = 0;
	k = 0;
	while (s1[i] != '\0' && i < n)
	{
		if (s1[i] == s2[k])
			k++;
		else
		{
			i = i - k;
			k = 0;
		}
		if (s2[k] == '\0')
			return ((char *)(&s1[i] - k + 1));
		i++;
	}
	return (NULL);
}
