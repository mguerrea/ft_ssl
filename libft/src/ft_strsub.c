/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 14:50:22 by mguerrea          #+#    #+#             */
/*   Updated: 2019/09/11 17:46:01 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (s)
	{
		if (!(str = ft_strnew(len)))
			return (NULL);
		i = -1;
		while (++i < len)
			str[i] = s[start + i];
		return (str);
	}
	else
		return (NULL);
}
