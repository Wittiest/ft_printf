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

int		(*g_funcs[])(t_start *) = 	{print_hex, print_hex, ft_putchar_arg,
									ft_putchar_arg, ft_putstr_arg, ft_putstr_arg
									,signed_arg, signed_arg, signed_arg, unsigned_arg,
									unsigned_arg, print_hex, unsigned_arg, unsigned_arg}; // poO
char	g_conversion[15] = "xXcCsSdiDuUpoO\0";

/*
**	As there is no type which is implicitly bigger than 4 bytes, I will read an
**	int for each unless given a length modifier. Types smaller are promoted to
**	int for being passed in the variadic argument. They will need to be casted
**	later to deal with the case of an int passed with H for example.
*/

void	read_arg(t_start *start, char c)
{
	if (c == 'o' || c == 'O' || c == 'u' || c == 'U' || c == 'x' || c == 'X' ||
		c == 'c' || c == 'C' || c == 'S' || c == 's')
	{
		if ((start->length_mod == L) || c == 'S' || c == 's')
			start->u_arg = va_arg(start->args, unsigned long);
		else if (start->length_mod == LL)
			start->u_arg = va_arg(start->args, unsigned long long);
		else if (start->length_mod == J)
			start->u_arg = va_arg(start->args, uintmax_t);
		else if (start->length_mod == Z)
			start->u_arg = va_arg(start->args, size_t);
		else
			start->u_arg = va_arg(start->args, unsigned int); // shorten after with typecast for certain cases
		return ;
	}
	if (start->length_mod == L)
		start->arg = va_arg(start->args, long);
	else if (start->length_mod == LL)
		start->arg = va_arg(start->args, long long);
	else if (start->length_mod == J)
		start->arg = va_arg(start->args, intmax_t);
	else if (start->length_mod == Z)
		start->arg = va_arg(start->args, size_t);
	else
		start->arg = va_arg(start->args, int); // shorten after with typecast for certain cases
}

void	parse_conv_char(t_start *start)
{
	int			i;

	if (start->c == 'D' || start->c == 'O' || start->c == 'U')
		start->length_mod = L;
	read_arg(start, start->c);
	if (start->c == 'C' || start->c == 'S')
		start->length_mod = L;
	i = 0;
	while (g_conversion[i])
	{
		if (g_conversion[i] == start->c)
		{
			start->ret += g_funcs[i](start);
			break;
		}
		i++;
	}
	if (i == 15)
	{
		write(1, "Invalid conversion character\n", 31);
		exit(5);
	}
	// deal with precision in each
		// if precision
			// if s, precision determines max characters
		// if decimal, max of min_width, precision, num size
	// pass string to function with dispatch table (D == d, O == o, U == u due to previous l conversion)
		//typecast arg
		//print shit
		//return int printed amount
}