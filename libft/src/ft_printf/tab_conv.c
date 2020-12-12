/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_conv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 17:29:35 by mguerrea          #+#    #+#             */
/*   Updated: 2020/12/12 17:31:44 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const t_conv g_tab_conv[] = {
	{'c', conv_char},
	{'s', conv_string},
	{'p', conv_pointer},
	{'d', conv_int},
	{'i', conv_int},
	{'o', conv_oct},
	{'u', conv_uint},
	{'x', conv_hex_min},
	{'X', conv_hex_maj},
	{'f', conv_double},
	{'h' + 'd', conv_short},
	{'h' + 'i', conv_short},
	{'h' + 'o', conv_hoct},
	{'h' + 'u', conv_ushort},
	{'h' + 'x', conv_hhex_min},
	{'h' + 'X', conv_hhex_maj},
	{'h' + 'h' + 'd', conv_charnb},
	{'h' + 'h' + 'i', conv_charnb},
	{'h' + 'h' + 'o', conv_hhoct},
	{'h' + 'h' + 'u', conv_uchar},
	{'h' + 'h' + 'x', conv_hhhex_min},
	{'h' + 'h' + 'X', conv_hhhex_maj},
	{'l' + 'd', conv_long},
	{'l' + 'i', conv_long},
	{'l' + 'o', conv_loct},
	{'l' + 'u', conv_ulong},
	{'l' + 'x', conv_lhex_min},
	{'l' + 'X', conv_lhex_maj},
	{'l' + 'l' + 'd', conv_longlong},
	{'l' + 'l' + 'i', conv_longlong},
	{'l' + 'l' + 'o', conv_lloct},
	{'l' + 'l' + 'u', conv_ulonglong},
	{'l' + 'l' + 'x', conv_llhex_min},
	{'l' + 'l' + 'X', conv_llhex_maj},
	{'l' + 'f', conv_double},
	{'L' + 'f', conv_longdouble},
	{'%', print_percent},
	{0, conv_none}
};