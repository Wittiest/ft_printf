/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpearson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 03:16:37 by dpearson          #+#    #+#             */
/*   Updated: 2017/10/22 03:17:47 by dpearson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
#define FT_PRINTF_H

#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
//write
//malloc + free + exit
// (man 3 stdarg)

void	ft_printf(char *format, ...);
void    *ft_memset(void *b, int c, size_t len);
char    *ft_strnew(size_t size);
char    *ft_strncpy(char *dst, const char *src, size_t len);
char    *ft_strndup(const char *s1, size_t n);

typedef struct s_modifiers
{
	char				con_char;
	char				*str_before;
	short				hash;
	short				zero;
	short				minus;
	short				plus;
	short				space;

	int					min_field_width;
	int					precision;

	short				hh;
	short				h;
	short				l;
	short				ll;
	short				j;
	short				z;
	struct	s_modifiers *next;
}				t_modifiers;

extern	s_modifiers		*m_head;

#endif
/*
**	We take in a string and variadic arguments to replace the %d, etc.
**	We need to parse the initial string, looking for each of the % after it
**		- exception for / breakout and % breakout
**	
** Writes to Standard Output
*/

/*
You have to manage the following conversions:
	s - string of characters
	S - above with l modifier
	p - The void * pointer argument is printed in hexadecimal (as if by `%#x' or `%#lx').
	d - decimal (integer) number (base 10)
	D - convert long int to signed decimal
	i - usually synonymous to d
	o - convert int to unsigned octal
	O - convert long int to unsigned octal
	u - print decimal unsigned int
	U - convert long int to unsigned int
	x - unsigned int as a hexadecimal number
	X - same as above with upper-case letters
	c - The int argument is converted to an unsigned char, and the resulting character is written.
	C - above with l modifier

You must manage %% (and other escape characters like \n)

You must manage the flags:
	#
	0
	-
	+
	space

You must manage the minimum field-width: (number like "%9d" -- add spaces until 9 for field)

You must manage the precision: minimum number of digits to appear after decimal

You must manage the flags:
	hh - A following integer conversion corresponds to a signed char or unsigned char argument, or 
		a following n conversion corresponds to a pointer to a signed char argument.
	h - A following integer conversion corresponds to a short int or unsigned short int argument,
		or a following n conversion corresponds to a pointer to a short int argument.
	l - A following integer conversion corresponds to a long int or unsigned long int argument, or
		a following n conversion corresponds to a pointer to a long int argument, or a following c
		conversion corresponds to a wint_t argument, or a following s conversion corresponds to a
		pointer to wchar_t argument.
	ll - A following integer conversion corresponds to a long long int or unsigned long long int
		argument, or a following n conversion corresponds to a pointer to a long long int argument.
	j - A following integer conversion corresponds to an intmax_t or uintmax_t argument.
	z - A following integer conversion corresponds to a size_t or ssize_t argument.
*/