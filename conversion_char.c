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

int		(*g_funcs[])(t_start *) = {print_hex, print_hex, ft_putchar_arg,
	ft_putchar_arg, ft_putstr_arg, ft_putstr_arg,
	signed_handler, signed_handler, signed_handler,
	unsigned_arg_handler, unsigned_arg_handler,
	print_hex, print_octal, print_octal};
char	g_conversion[15] = "xXcCsSdiDuUpoO\0";

/*
**	As there is no type which is implicitly bigger than 4 bytes, I will read an
**	int for each unless given a length modifier. Types smaller are promoted to
**	int for being passed in the variadic argument. They will need to be casted
**	later to deal with the case of an int passed with H for example.
*/

static void	read_arg(t_start *start, char c)
{
	if (c == 'd' || c == 'D' || c == 'i')
	{
		if (start->l_mod == L)
			start->arg = va_arg(start->args, long);
		else if (start->l_mod == LL)
			start->arg = va_arg(start->args, long long);
		else if (start->l_mod == J)
			start->arg = va_arg(start->args, intmax_t);
		else if (start->l_mod == Z)
			start->arg = va_arg(start->args, size_t);
		else
			start->arg = va_arg(start->args, int);
		return ;
	}
	if (start->l_mod == Z || c == 'S' || c == 's' || c == 'p')
		start->u_arg = va_arg(start->args, size_t);
	else if (start->l_mod == L)
		start->u_arg = va_arg(start->args, unsigned long);
	else if (start->l_mod == LL)
		start->u_arg = va_arg(start->args, unsigned long long);
	else if (start->l_mod == J)
		start->u_arg = va_arg(start->args, uintmax_t);
	else
		start->u_arg = va_arg(start->args, unsigned int);
}

static void	demote_int(t_start *start)
{
	if (start->c == 'd' || start->c == 'i')
	{
		if (start->l_mod == H)
			start->arg = (short)start->arg;
		else if (start->l_mod == HH)
			start->arg = (signed char)start->arg;
	}
	else
	{
		if (start->l_mod == H)
			start->arg = (unsigned short)start->arg;
		else if (start->l_mod == HH)
			start->arg = (unsigned char)start->arg;
	}
}

void		parse_conv_char(t_start *start)
{
	int			i;

	if (start->c == 'D' || start->c == 'O' || start->c == 'U')
		start->l_mod = L;
	read_arg(start, start->c);
	demote_int(start);
	if (start->c == 'C' || start->c == 'S')
		start->l_mod = L;
	i = 0;
	while (g_conversion[i])
	{
		if (g_conversion[i] == start->c)
		{
			start->ret += g_funcs[i](start);
			break ;
		}
		i++;
	}
	if (i == 15)
	{
		write(1, "Invalid conversion character\n", 31);
		exit(5);
	}
}
