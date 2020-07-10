/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 14:19:33 by mguerrea          #+#    #+#             */
/*   Updated: 2019/09/10 15:35:09 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_words(char const *str, char c)
{
	int is_word;
	int i;
	int count;

	is_word = 0;
	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c && is_word == 0)
		{
			is_word = 1;
			count++;
		}
		if (str[i] == c && is_word == 1)
			is_word = 0;
		i++;
	}
	return (count);
}

static int		count_letters(char const *str, char c)
{
	int i;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	return (i);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**array;
	int		j;

	if (s)
	{
		j = 0;
		if (!(array = (char **)malloc(sizeof(char *)
			* (count_words(s, c) + 1))))
			return (NULL);
		while (*s != '\0')
		{
			while (*s == c)
				s++;
			if (*s == '\0')
				break ;
			if (!(array[j] = ft_strsub((char *)s, 0, count_letters(s, c))))
				return (NULL);
			s += count_letters(s, c);
			j++;
		}
		array[j] = NULL;
		return (array);
	}
	return (NULL);
}
