/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpearson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 03:16:37 by dpearson          #+#    #+#             */
/*   Updated: 2017/12/24 12:58:20 by dpearson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdint.h>
# include <wchar.h>

enum			e_length
{
	H = 1,
	HH = 2,
	L = 3,
	LL = 4,
	J = 5,
	Z = 6
};

typedef struct	s_flags
{
	short		hash;
	short		zero;
	short		plus;
	short		minus;
	short		space;
}				t_flags;

typedef struct	s_start
{
	int			ret;
	char		*format;
	char		c;
	va_list		args;
	t_flags		flags;
	int			min_width;
	int			prec;
	int			zero_prec;
	short		l_mod;
	intmax_t	arg;
	uintmax_t	u_arg;
	short		plus_done;
	int			neg;
}				t_start;

int				ft_printf(char *format, ...);
void			printstr(int begin, int end, t_start *start);
void			zero_flags(t_start *start);
int				escape_check(t_start *start, int *i);
void			parse_conv_char(t_start *start);
void			parser(t_start *start);
int				signed_count(intmax_t n);
size_t			unsigned_count(uintmax_t n, int base);
void			fix_prefix(t_start *start);

int				print_hex(t_start *start);
int				ft_putstr_arg(t_start *start);
int				ft_putchar_arg(t_start *start);
int				signed_handler(t_start *start);
int				print_octal(t_start *start);
int				unsigned_arg_handler(t_start *start);
#endif
