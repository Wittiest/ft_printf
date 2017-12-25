/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpearson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 10:27:54 by dpearson          #+#    #+#             */
/*   Updated: 2017/12/25 10:27:55 by dpearson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//sSpdDioOuUxXcC

/*
**	As there is no type which is implicitly bigger than 4 bytes, I will read an
**	int for each unless given a length modifier. Types smaller are promoted to
**	int for being passed in the variadic argument. They will need to be casted
**	later to deal with the case of an int passed with H for example.
*/

void	read_arg(t_start *start, intmax_t *arg, uintmax_t *u_arg, uint8_t un)
{
	if (un)
	{
		if (start->length_mod == L)
			*u_arg = va_arg(start->args, unsigned long);
		else if (start->length_mod == LL)
			*u_arg = va_arg(start->args, unsigned long long);
		else if (start->length_mod == J)
			*u_arg = va_arg(start->args, uintmax_t);
		else if (start->length_mod == Z)
			*u_arg = va_arg(start->args, size_t);
		else
			*u_arg = va_arg(start->args, unsigned int); // shorten after with typecast for certain cases
		return ;
	}
	if (start->length_mod == L)
		*arg = va_arg(start->args, long);
	else if (start->length_mod == LL)
		*arg = va_arg(start->args, long long);
	else if (start->length_mod == J)
		*arg = va_arg(start->args, intmax_t);
	else if (start->length_mod == Z)
		*arg = va_arg(start->args, size_t); // signed with d or i. Just size of size_t
	else
		*arg = va_arg(start->args, int); // shorten after with typecast for certain cases
}

void	parse_conv_char(t_start *start, int *i)
{
	intmax_t	arg;
	uintmax_t	u_arg;
	char		c;

	c = start->format[(*i)++];
	if (c == 'D' || c == 'O' || c == 'U')
		start->length_mod = L;
	read_arg(start, &arg, &u_arg, ((c == 'o' || c == 'O' || c == 'u' || c == 'U'
									|| c == 'x' || c == 'X' || c == 's' ||
									c == 'S' || c == 'c' || c == 'C') ? 1 : 0));
	// malloc the string
		// if precision
			// if s, precision determines max characters
		// if decimal, max of min_width, precision, num size
	//create large static string for shit. Handle it in a function. Store in this one
	// pass string to function with dispatch table (D == d, O == o, U == u due to previous l conversion)
		//typecast arg
		//print shit
		//return int printed amount
}