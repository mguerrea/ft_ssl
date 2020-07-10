/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddback.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 19:21:24 by mguerrea          #+#    #+#             */
/*   Updated: 2018/11/18 12:35:38 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddback(t_list **list, t_list *new)
{
	t_list *temp;

	if (!list)
		return ;
	temp = *list;
	if (!temp)
	{
		*list = new;
		return ;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}
