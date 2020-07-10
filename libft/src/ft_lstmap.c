/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 16:48:39 by mguerrea          #+#    #+#             */
/*   Updated: 2018/11/05 15:50:59 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*first;
	t_list	*tmp;

	if (!lst)
		return (NULL);
	if (!(tmp = f(lst)))
		return (NULL);
	first = tmp;
	lst = lst->next;
	while (lst)
	{
		if (!(tmp->next = f(lst)))
			return (NULL);
		lst = lst->next;
		tmp = tmp->next;
	}
	return (first);
}
