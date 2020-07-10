/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 12:31:59 by mguerrea          #+#    #+#             */
/*   Updated: 2019/09/30 12:32:02 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t o_size, size_t n_size)
{
	void	*new;

	if (n_size == 0)
	{
		ft_memdel(&ptr);
		return (NULL);
	}
	if (!(new = ft_memalloc(n_size)))
		return (NULL);
	if (ptr && o_size)
	{
		if (o_size > n_size)
			ft_memcpy(new, ptr, n_size);
		else
			ft_memcpy(new, ptr, o_size);
		ft_memdel(&ptr);
	}
	return (new);
}
