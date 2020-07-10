/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 15:10:12 by mguerrea          #+#    #+#             */
/*   Updated: 2018/12/17 12:29:26 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;
	unsigned int	len;

	str = NULL;
	if (s)
	{
		if (!(str = ft_strnew(ft_strlen((char *)s))))
			return (NULL);
		i = -1;
		len = ft_strlen((char *)s);
		while (++i < len)
			str[i] = f(i, s[i]);
	}
	return (str);
}
