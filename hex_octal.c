/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_octal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpearson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 17:14:55 by dpearson          #+#    #+#             */
/*   Updated: 2017/12/25 17:15:02 by dpearson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		print_hex_low(uintmax_t	u_arg, int p, int hash)
{
	char	low_hex[17] = "0123456789abcdef";
	int		i;

	i = (p || (hash && u_arg)) ? write(1, "0x", 2) : 0;
	if (u_arg >= 16)
		i += print_hex_low(u_arg / 16, 0, 0);
	write(1, &low_hex[u_arg % 16], 1);
	return (1 + i);
}
static int		print_hex_upp(uintmax_t	u_arg, int hash)
{
	char	upp_hex[17] = "0123456789ABCDEF";
	int		i;

	i = (hash && u_arg) ? write(1, "0X", 2) : 0;
	if (u_arg >= 16)
		i += print_hex_upp(u_arg / 16, 0);
	write(1, &upp_hex[u_arg % 16], 1);
	return (1 + i);
}

int		print_hex(t_start *start) // PRECISION??
{
	size_t	total_print_len;
	size_t	hex;
	size_t	printed;

	hex = unsigned_count(start->u_arg, 16) + ((start->flags.hash || (start->c == 'p')) * 2);
	total_print_len = (start->min_width > (int)hex) ? start->min_width : hex;
	if (start->flags.minus)
	{
		if (start->c == 'X')
			printed = print_hex_upp(start->u_arg, start->flags.hash);
		else
			printed = print_hex_low(start->u_arg, start->c == 'p', start->flags.hash);
		while (printed++ < total_print_len)
			write(1, ((start->flags.zero) ? "0" : " "), 1);
	}
	else
	{
		if (start->c == 'X')
			print_hex_upp(start->u_arg, start->flags.hash);
		else
			print_hex_low(start->u_arg, start->c == 'p', start->flags.hash);
		while (++hex <= total_print_len)
			write(1, ((start->flags.zero) ? "0" : " "), 1);
	}
	return (total_print_len);
}

static int	print_oct(uintmax_t t, int hash)
{
	int		ret;
	char	c;

	ret = (hash && t) ? write(1, "0", 1) : 0;
	if (t >= 8)
		ret += print_oct((t / 8), 0);
	c = (t % 8) + '0';
	write(1, &c, 1);
	return (1 + ret);
}

int		print_octal(t_start *start)
{
	size_t	total_len;

	total_len = unsigned_count(start->u_arg, 8) + start->flags.hash;
	return(print_oct(start->u_arg, start->flags.hash));
}
