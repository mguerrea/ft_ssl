/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 15:11:49 by mguerrea          #+#    #+#             */
/*   Updated: 2018/12/17 12:30:27 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
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
			str[i] = f(s[i]);
	}
	return (str);
}
