/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_to_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 14:43:22 by mguerrea          #+#    #+#             */
/*   Updated: 2018/11/05 14:44:27 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_list_to_str(t_list *list)
{
	size_t	size;
	t_list	*temp;
	char	*str;

	temp = list;
	size = 0;
	while (temp)
	{
		size = size + temp->content_size - 1;
		temp = temp->next;
	}
	if (!(str = ft_strnew(size)))
		return (NULL);
	temp = list;
	while (temp)
	{
		str = ft_strcat(str, temp->content);
		temp = temp->next;
	}
	return (str);
}
