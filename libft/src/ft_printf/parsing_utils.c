/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 14:12:00 by gmichaud          #+#    #+#             */
/*   Updated: 2020/12/12 17:32:06 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

extern const t_conv g_tab_conv[];

int		find_conv_function(int type)
{
	int	i;

	i = 0;
	while (g_tab_conv[i].format && g_tab_conv[i].format != type)
		i++;
	return (i);
}

void	init_formating(t_options *options, int *type, int fd)
{
	options->flags = 0;
	options->precision = -1;
	options->field_size = 0;
	options->fd = fd;
	*type = 0;
}

void	parse_digits(t_options *options, const char *format)
{
	if (!options->field_size && options->precision == -1)
		options->field_size = ft_atoi(format);
	else if (!options->precision)
		options->precision = ft_atoi(format);
}

int		conv(t_options *options, int type, char conv_type)
{
	if (conv_type == 'p')
	{
		options->flags |= ALT;
		type = 0;
	}
	return (type + conv_type);
}

void	get_flag(t_options *options, const char *flags, char flag_type)
{
	if (flag_type != '0' || (!options->field_size && options->precision == -1))
		options->flags |= (1 << (ft_strchr(flags, flag_type) - flags));
}
