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

int		print_hex(t_start *start)
{
	int		total_print_len;
	int		hex;
	int		printed;

	printed = 0;
	fix_prefix(start);
	hex = unsigned_count(start->u_arg, 16) + (((start->flags.hash && start->u_arg) || (start->c == 'p')) * 2);
	start->prec = (start->prec < hex) ? 0 : start->prec;
	total_print_len = (start->min_width > hex) ? start->min_width : hex;
	if (!start->min_width)
		total_print_len -= ((!start->zero_prec || start->u_arg)) ? 0 : 1;
	hex -= ((!start->zero_prec || start->u_arg)) ? 0 : 1;
	if (start->flags.minus)
	{
		while ((start->prec) ? (printed++ < start->prec) : 0)
			write(1, "0", 1);
		if (start->c == 'X' && (!start->zero_prec || start->u_arg))
			printed += print_hex_upp(start->u_arg, start->flags.hash);
		else if (!start->zero_prec || start->u_arg)
			printed += print_hex_low(start->u_arg, start->c == 'p', start->flags.hash);
		while (printed++ < total_print_len)
			write(1, " ", 1);
	}
	else
	{
		while ((((start->prec) ? (printed++) : (hex++)) < (total_print_len - start->prec)))
			write(1, ((start->flags.zero && !start->prec) ? "0" : " "), 1);
		while (hex++ < start->prec)
			write(1, "0", 1);
		if (start->c == 'X' && (!start->zero_prec || start->u_arg))
			print_hex_upp(start->u_arg, start->flags.hash);
		else if (!start->zero_prec || start->u_arg)
			print_hex_low(start->u_arg, start->c == 'p', start->flags.hash);
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
	int		total_len;
	int		oct;
	int		printed;

	printed = 0;
	oct = unsigned_count(start->u_arg, 8) + (start->flags.hash && start->u_arg);
	start->prec = (start->prec < oct) ? 0 : start->prec;
	total_len = (start->min_width > oct) ? start->min_width : oct;
	if (start->flags.minus)
	{
		while ((start->prec) ? (printed++ < start->prec) : 0)
			write(1, "0", 1);
			printed += print_oct(start->u_arg, start->flags.hash);
		while (printed++ < total_len)
			write(1, " ", 1);
	}
	else
	{
		while ((((start->prec) ? (printed++) : (oct++)) < (total_len - start->prec)))
			write(1, ((start->flags.zero && !start->prec) ? "0" : " "), 1);
		while (oct++ < start->prec)
			write(1, "0", 1);
		print_oct(start->u_arg, start->flags.hash);
	}
	return (total_len);
}
