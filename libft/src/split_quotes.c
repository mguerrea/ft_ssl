/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 17:58:43 by mguerrea          #+#    #+#             */
/*   Updated: 2020/07/14 19:04:26 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *str, char c)
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

static int	count_letters(char const *str, char c)
{
	int i;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	return (i);
}

static char	**fill_tab(char **arr, char const *s, char c)
{
	int j;
	int len;

	j = 0;
	while (*s != 0)
	{
		while (*s == c)
			s++;
		if (*s == 0)
			break ;
		if (*s == '\"')
			len = count_letters(++s, '\"');
		else
			len = count_letters(s, c);
		if (!(arr[j] = ft_strsub((char *)s, 0, len)))
			return (NULL);
		s += (*(s + len) == '\"') + len;
		j++;
	}
	arr[j] = NULL;
	return (arr);
}

char		**split_quotes(char const *s, char c)
{
	char **array;

	if (s)
	{
		if (!(array = (char **)malloc(sizeof(char *)
			* (count_words(s, c) + 1))))
			return (NULL);
		return (fill_tab(array, s, c));
	}
	return (NULL);
}
