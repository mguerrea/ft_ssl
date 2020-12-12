/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguerrea <mguerrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 13:33:09 by gmichaud          #+#    #+#             */
/*   Updated: 2020/12/12 17:34:29 by mguerrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

# define NBTYPES 38

typedef enum	e_flags
{
	ALT = 1 << 0,
	PADD_RIGHT = 1 << 1,
	SIGN = 1 << 2,
	SPACE = 1 << 3,
	ZERO = 1 << 4
}				t_flags;

typedef struct	s_options
{
	t_flags		flags;
	size_t		field_size;
	int			precision;
	int			fd;
}				t_options;

typedef int		(*t_print_fct)(va_list ap, t_options);

typedef struct s_conv
{
	int format;
	t_print_fct function;
	
}			t_conv;

void			print_padding(int len, char c, int fd);
long long		ft_llabs(long long n);
double			ft_pow(int x, int y);
int				conv_int(va_list ap, t_options options);
int				conv_long(va_list ap, t_options options);
int				conv_longlong(va_list ap, t_options options);
int				conv_short(va_list ap, t_options options);
int				conv_charnb(va_list ap, t_options options);
int				conv_uint(va_list ap, t_options options);
int				conv_ulong(va_list ap, t_options options);
int				conv_ulonglong(va_list ap, t_options options);
int				conv_ushort(va_list ap, t_options options);
int				conv_uchar(va_list ap, t_options options);
int				conv_string(va_list ap, t_options options);
int				print(const char *s, t_options options);
int				printchar(char c, t_options options);
int				conv_hex_min(va_list ap, t_options options);
int				conv_hex_maj(va_list ap, t_options options);
char			*ft_lltoa_base(unsigned long long nb, int base, char type,
	t_options options);
char			*ft_lltoa_form(long long n, t_options options);
char			*ft_ulltoa_form(unsigned long long n, t_options options);
char			*ft_lltoa(long long n);
int				conv_char(va_list ap, t_options options);
int				conv_double(va_list ap, t_options options);
int				conv_longdouble(va_list ap, t_options options);
int				conv_oct(va_list ap, t_options options);
int				conv_hhex_min(va_list ap, t_options options);
int				conv_hhex_maj(va_list ap, t_options options);
int				conv_hhhex_min(va_list ap, t_options options);
int				conv_hhhex_maj(va_list ap, t_options options);
int				conv_lhex_maj(va_list ap, t_options options);
int				conv_lhex_min(va_list ap, t_options options);
int				conv_llhex_maj(va_list ap, t_options options);
int				conv_llhex_min(va_list ap, t_options options);
int				conv_loct(va_list ap, t_options options);
int				conv_lloct(va_list ap, t_options options);
int				conv_hoct(va_list ap, t_options options);
int				conv_hhoct(va_list ap, t_options options);
char			*ft_dtoa(double f, t_options options);
int				ft_max(int a, int b);
char			*ft_ldtoa(long double f, t_options options);
int				ft_printf(char *format, ...);
int				print_percent(va_list ap, t_options options);
double			ft_pow(int x, int y);
long long		ft_llabs(long long n);
int				find_conv_function(int type);
void			init_formating(t_options *options, int *type, int fd);
void			parse_digits(t_options *options, const char *format);
int				conv(t_options *options, int type, char conv_type);
void			get_flag(t_options *options, const char *flags, char flag_type);
int				conv_pointer(va_list ap, t_options options);
int				conv_none(va_list ap, t_options options);
char			*ft_endcpy(char *dest, char *src, int n);
int				ft_dprintf(int fd, char *format, ...);
int				parsing(char *format, va_list ap, int fd);

#endif
