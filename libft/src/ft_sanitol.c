/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sanitol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 17:22:14 by mguerrea          #+#    #+#             */
/*   Updated: 2018/11/05 15:25:12 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sanitol(char *str)
{
	char	*copy;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(copy = ft_strnew(ft_strlen(str))))
		return ;
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && str[i] != '\t')
		{
			copy[j] = str[i];
			j++;
		}
		i++;
	}
	copy[j] = '\0';
	ft_strcpy(str, copy);
	free(copy);
}
