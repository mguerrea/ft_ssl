/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_elem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 13:27:48 by mguerrea          #+#    #+#             */
/*   Updated: 2018/12/18 13:30:09 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_elem(t_list **list)
{
	t_list	*temp;
	int		count;

	count = 0;
	if (!list)
		return (0);
	temp = *list;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}
