/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 12:34:24 by gmichaud          #+#    #+#             */
/*   Updated: 2016/11/15 16:58:46 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*ptr;

	ptr = NULL;
	i = 0;
	k = 0;
	if (needle[0] == '\0')
		return ((char*)haystack);
	while (haystack[k])
	{
		j = 0;
		i = k;
		ptr = (char*)haystack + k;
		while (haystack[i] && needle[j] && haystack[i] == needle[j])
		{
			j++;
			i++;
		}
		if (needle[j] == '\0')
			return (ptr);
		k++;
	}
	return (NULL);
}
