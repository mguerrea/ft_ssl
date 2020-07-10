/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/06 10:27:39 by gmichaud          #+#    #+#             */
/*   Updated: 2018/12/31 12:51:47 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *s)
{
	int flag;
	int res;
	int i;

	flag = 0;
	res = 0;
	i = 0;
	while ((s[i] == ' ' || (s[i] >= 9 && s[i] <= 13)) && s[i])
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		flag = i;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + (s[i] - 48);
		i++;
	}
	if (s[flag] == '-')
		res = -res;
	return (res);
}
