/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decimal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpearson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 18:08:56 by dpearson          #+#    #+#             */
/*   Updated: 2017/12/25 18:08:56 by dpearson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	signed_arg(intmax_t arg, int neg)
{
	char	str[100];
	int		i;

	i = 0;
	if (!arg && ++i)
		str[0] = '0';
	while ((arg) > 0 || ((neg) && (arg < 0)))
	{
		str[i] = '0' + ((neg) ? -(arg % 10) : (arg % 10));
		arg /= 10;
		i++;
	}
	while (--i >= 0)
		neg += write(1, &str[i], 1);
	return (neg);
}

int		signed_handler(t_start *start)
{
	int		p;
	int		neg;
	int		total_len;
	int		printed;

	printed = neg = (start->arg < 0) ? 1 : 0;
	p = signed_count(start->arg) + (start->flags.space || start->flags.plus || neg);
	total_len = (p > start->min_width) ? p : start->min_width;
	start->prec = (start->prec < p) ? 0 : start->prec;
	if (start->prec > start->min_width)
	{
		total_len = (total_len > (start->prec + (start->flags.space ||
		start->flags.plus || neg))) ? total_len : (start->prec +
		(start->flags.space || start->flags.plus || neg));
		start->flags.zero = 1;
	}
	if (!start->min_width)
		total_len -= ((start->zero_prec && !start->arg)) ? 1 : 0;
	if (neg && start->flags.zero)
		write(1, "-", 1);
	if (start->flags.minus)
	{
		if ((start->flags.space || start->flags.plus) && !neg)
			printed += write(1, (start->flags.plus) ? "+" : " ", 1);
		if (neg && !start->flags.zero)
			write(1, "-", 1);
		while (((p++ - (start->flags.space || start->flags.plus || neg)) < start->prec) && ++printed)
			write(1, "0", 1);
		if (!start->zero_prec || start->arg)
			printed += signed_arg(start->arg, neg) - ((neg) ? 1 : 0);
		while (printed++ < start->min_width)
			write(1, " ", 1);
	}
	else
	{
		if (((start->flags.space || start->flags.plus) && !neg) && (!(start->min_width && !start->flags.zero) || printed++))
			printed += write(1, (start->flags.plus) ? "+" : " ", 1);
		while ((((start->prec || (start->zero_prec && !start->arg)) ? (printed++) : (p++)) < (total_len - start->prec)))
			write(1, ((start->flags.zero && !start->prec) ? "0" : " "), 1);
		// add check for % 4.5i 42 == | 00042| to allow plus placement to not affect precision badly
		if ((!start->flags.zero && start->min_width) && (start->flags.space || start->flags.plus) && !neg)
			p -= write(1, (start->flags.plus) ? "+" : " ", 1);
		while ((p++ - neg < start->prec))
			write(1, "0", 1);
		if (neg && !start->flags.zero)
			write(1, "-", 1);
		if (!start->zero_prec || start->arg)
			signed_arg(start->arg, neg);
	}
	return(total_len);
}

static int	unsigned_arg(uintmax_t u_arg)
{
	char	str[100];
	int		i;
	int		j;

	i = 0;
	if (!u_arg && ++i)
		str[0] = '0';
	while ((u_arg) > 0)
	{
		str[i] = '0' + (u_arg % 10);
		u_arg /= 10;
		i++;
	}
	j = i;
	while (--i >= 0)
		write(1, &str[i], 1);
	return (j);
}

int		unsigned_arg_handler(t_start *start)
{
	int		un;
	int		printed;
	int		total_len;

	printed = 0;
	un = unsigned_count(start->u_arg, 10);
	total_len = (start->min_width > un) ? start->min_width : un;
	if (start->prec > start->min_width)
	{
		total_len = (total_len > start->prec) ? total_len : start->prec;
		start->flags.zero = 1;
	}
	if (start->flags.minus)
	{
		printed += unsigned_arg(start->u_arg);
		while (printed++ < start->min_width)
			write(1, ((start->flags.zero) ? "0" : " "), 1);
	}
	else
	{
		while (un++ < total_len)
			write(1, ((start->flags.zero) ? "0" : " "), 1);
		unsigned_arg(start->u_arg);
	}
	return (total_len);
}
