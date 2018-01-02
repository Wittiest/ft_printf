/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpearson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 00:02:36 by dpearson          #+#    #+#             */
/*   Updated: 2018/01/02 00:02:37 by dpearson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
	fix_prefix(start);
	oct = unsigned_count(start->u_arg, 8) + (start->flags.hash && start->u_arg);
	start->prec = (start->prec < oct) ? 0 : start->prec;
	total_len = (start->min_width > oct) ? start->min_width : oct;
	if (!start->min_width && !start->flags.hash)
		total_len -= ((!start->zero_prec || start->u_arg)) ? 0 : 1;
	if (start->prec > start->min_width)
		total_len = (total_len > start->prec) ? total_len : start->prec;
	if (start->flags.minus)
	{
		printed = oct;
		while ((start->prec) ? (printed++ < (start->prec)) : 0)
			write(1, "0", 1);
		printed -= (start->prec) ? oct + 1: oct;
		printed += print_oct(start->u_arg, start->flags.hash);
		while (printed++ < total_len)
			write(1, " ", 1);
	}
	else
	{
		if (start->zero_prec)
			oct = start->prec;
		while ((((start->prec) ? (printed++) : (oct++)) < (total_len - start->prec)))
			write(1, ((start->flags.zero && !start->prec) ? "0" : " "), 1);
		while (oct++ < start->prec)
			write(1, "0", 1);
		if ((!start->zero_prec || start->u_arg))
			print_oct(start->u_arg, start->flags.hash);
	}
	return (total_len);
}