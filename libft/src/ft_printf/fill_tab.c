/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 15:54:32 by mguerrea          #+#    #+#             */
/*   Updated: 2018/12/31 16:33:57 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		fill_print2(t_print_fct *print)
{
	print[16] = conv_charnb;
	print[17] = conv_charnb;
	print[18] = conv_hhoct;
	print[19] = conv_uchar;
	print[20] = conv_hhhex_min;
	print[21] = conv_hhhex_maj;
	print[22] = conv_long;
	print[23] = conv_long;
	print[24] = conv_loct;
	print[25] = conv_ulong;
	print[26] = conv_lhex_min;
	print[27] = conv_lhex_maj;
	print[28] = conv_longlong;
	print[29] = conv_longlong;
	print[30] = conv_lloct;
	print[31] = conv_ulonglong;
	print[32] = conv_llhex_min;
	print[33] = conv_llhex_maj;
	print[34] = conv_double;
	print[35] = conv_longdouble;
	print[36] = print_percent;
	print[37] = conv_none;
}

void			fill_print(t_print_fct *print)
{
	print[0] = conv_char;
	print[1] = conv_string;
	print[2] = conv_pointer;
	print[3] = conv_int;
	print[4] = conv_int;
	print[5] = conv_oct;
	print[6] = conv_uint;
	print[7] = conv_hex_min;
	print[8] = conv_hex_maj;
	print[9] = conv_double;
	print[10] = conv_short;
	print[11] = conv_short;
	print[12] = conv_hoct;
	print[13] = conv_ushort;
	print[14] = conv_hhex_min;
	print[15] = conv_hhex_maj;
	fill_print2(print);
}

static void		fill_type2(int *tab_type)
{
	tab_type[16] = 'h' + 'h' + 'd';
	tab_type[17] = 'h' + 'h' + 'i';
	tab_type[18] = 'h' + 'h' + 'o';
	tab_type[19] = 'h' + 'h' + 'u';
	tab_type[20] = 'h' + 'h' + 'x';
	tab_type[21] = 'h' + 'h' + 'X';
	tab_type[22] = 'l' + 'd';
	tab_type[23] = 'l' + 'i';
	tab_type[24] = 'l' + 'o';
	tab_type[25] = 'l' + 'u';
	tab_type[26] = 'l' + 'x';
	tab_type[27] = 'l' + 'X';
	tab_type[28] = 'l' + 'l' + 'd';
	tab_type[29] = 'l' + 'l' + 'i';
	tab_type[30] = 'l' + 'l' + 'o';
	tab_type[31] = 'l' + 'l' + 'u';
	tab_type[32] = 'l' + 'l' + 'x';
	tab_type[33] = 'l' + 'l' + 'X';
	tab_type[34] = 'l' + 'f';
	tab_type[35] = 'L' + 'f';
	tab_type[36] = '%';
	tab_type[37] = 0;
}

void			fill_type(int *tab_type)
{
	tab_type[0] = 'c';
	tab_type[1] = 's';
	tab_type[2] = 'p';
	tab_type[3] = 'd';
	tab_type[4] = 'i';
	tab_type[5] = 'o';
	tab_type[6] = 'u';
	tab_type[7] = 'x';
	tab_type[8] = 'X';
	tab_type[9] = 'f';
	tab_type[10] = 'h' + 'd';
	tab_type[11] = 'h' + 'i';
	tab_type[12] = 'h' + 'o';
	tab_type[13] = 'h' + 'u';
	tab_type[14] = 'h' + 'x';
	tab_type[15] = 'h' + 'X';
	fill_type2(tab_type);
}
