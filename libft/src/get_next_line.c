/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:35:30 by mguerrea          #+#    #+#             */
/*   Updated: 2020/01/23 12:21:15 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	stocktoline(char **stock, char **line)
{
	char	*tmp;
	size_t	len;

	len = 0;
	while ((*stock)[len] && (*stock)[len] != '\n')
		len++;
	if (!(*line = ft_strnew(sizeof(**line) * len)))
		return (-1);
	*line = ft_strncpy(*line, *stock, len);
	if (((*stock)[len] && !(*stock)[len + 1]) || !(*stock)[len])
	{
		ft_strdel(stock);
		return (1);
	}
	if (!(tmp = ft_strnew(sizeof(*tmp) * (ft_strlen(*stock) - len - 1))))
		return (-1);
	tmp = ft_strcpy(tmp, *stock + len + 1);
	free(*stock);
	*stock = tmp;
	return (1);
}

static int	bufftostock(char *buff, char **stock, size_t size)
{
	size_t	o_len;

	buff[size] = '\0';
	o_len = (*stock ? ft_strlen(*stock) : 0);
	if (!(*stock = ft_realloc(*stock, o_len, o_len + size + 1)))
		return (-1);
	while (size--)
	{
		(*stock)[o_len++] = *buff;
		buff++;
	}
	(*stock)[o_len] = '\0';
	return (ft_strchr(*stock, '\n') ? 1 : 0);
}

char		*getstock(t_list *file_lst, int fd)
{
	while (file_lst)
	{
		if (((t_file*)file_lst->content)->fd == fd)
			return (((t_file*)file_lst->content)->stock);
		file_lst = file_lst->next;
	}
	return (NULL);
}

void		manage_lst(t_list **file_lst, int fd, char *stock, int ret)
{
	t_file	file;
	t_list	*prec;
	t_list	*tmp;

	file.fd = fd;
	file.stock = stock;
	prec = *file_lst;
	tmp = *file_lst;
	while (tmp && ((t_file*)tmp->content)->fd != fd)
		tmp = tmp->next;
	if (!tmp)
		ft_lstadd(file_lst, ft_lstnew(&file, sizeof(file)));
	else
	{
		((t_file*)tmp->content)->stock = stock;
		while (prec != tmp && prec->next != tmp)
			prec = prec->next;
		if (!stock && !ret)
		{
			prec->next = prec ? tmp->next : prec->next;
			*file_lst = (prec == *file_lst) ? (*file_lst)->next : *file_lst;
			free(tmp->content);
			free(tmp);
		}
	}
}

int			get_next_line(int fd, char **line)
{
	char			*buff;
	static t_list	*file_lst = NULL;
	char			*stock;
	ssize_t			ret;
	int				flg;

	if (fd < 0 || BUFF_SIZE == 0)
		return (-1);
	stock = getstock(file_lst, fd);
	flg = (stock && ft_strchr(stock, '\n')) ? 1 : 0;
	if (!(buff = (char*)ft_memalloc(sizeof(char) * (BUFF_SIZE + 1))))
		return (-1);
	ret = 1;
	while (!flg && (ret = read(fd, buff, BUFF_SIZE)) > 0)
		flg = bufftostock(buff, &stock, ret);
	ft_memdel((void**)&buff);
	if (flg == -1 || ret == -1)
		return (-1);
	if (stock)
		flg = stocktoline(&stock, line);
	manage_lst(&file_lst, fd, stock, ret);
	if (flg == 0 && ret == 0)
		return (0);
	return (1);
}
