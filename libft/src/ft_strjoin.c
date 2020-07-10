/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 15:13:12 by mguerrea          #+#    #+#             */
/*   Updated: 2019/09/06 14:10:44 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len;

	if (s1 && s2)
	{
		len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
		if (!(str = ft_strnew(len)))
			return (NULL);
		str = ft_strcat(str, s1);
		str = ft_strcat(str, s2);
		return (str);
	}
	else
		return (NULL);
}
