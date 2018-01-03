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
#include <stdio.h> // REMOVER
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

static void	signed_minus(t_start *start, int p, int printed)
{
	if ((start->flags.space || start->flags.plus) && !start->neg)
		printed += write(1, (start->flags.plus) ? "+" : " ", 1);
	if (start->neg && !start->flags.zero)
		write(1, "-", 1);
	while (((p++ - (start->flags.space || start->flags.plus || start->neg)) <
		start->prec) && ++printed)
		write(1, "0", 1);
	if (!start->zero_prec || start->arg)
		printed += signed_arg(start->arg, start->neg) - ((start->neg) ? 1 : 0);
	while (printed++ < start->min_width)
		write(1, " ", 1);
}

static void signed_unminus(t_start *start, int p, int printed, int total_len)
{
	if (((start->flags.space || start->flags.plus) && !start->neg))
		if (!(start->min_width && !start->flags.zero) || printed++)
		{
			printed += write(1, (start->flags.plus) ? "+" : " ", 1);
			if (start->min_width < start->prec)
				p -= 1;
		}
	if (start->prec || (start->zero_prec && !start->arg))
		while (printed++ < (total_len - start->prec))
			write(1, ((start->flags.zero && !start->prec) ? "0" : " "), 1);
	else
		while (p++ < (total_len - start->prec))
			write(1, ((start->flags.zero && !start->prec) ? "0" : " "), 1);		
	if ((!start->flags.zero && start->min_width) && (start->flags.space ||
		start->flags.plus) && !start->neg)
		p -= write(1, (start->flags.plus) ? "+" : " ", 1);
	while ((p++ - start->neg < start->prec))
		write(1, "0", 1);
	if (start->neg && !start->flags.zero)
		write(1, "-", 1);
	if (!start->zero_prec || start->arg)
		signed_arg(start->arg, start->neg);
}

int			signed_handler(t_start *start)
{
	int		p;
	int		total_len;
	int		printed;

	start->neg = (start->arg < 0) ? 1 : 0;
	printed = start->neg;
	p = signed_count(start->arg) + (start->flags.space ||
		start->flags.plus || start->neg);
	total_len = (p > start->min_width) ? p : start->min_width;
	start->prec = (start->prec < p) ? 0 : start->prec;
	if (start->prec > start->min_width)
	{
		total_len = (total_len > (start->prec + (start->flags.space ||
		start->flags.plus || start->neg))) ? total_len : (start->prec +
		(start->flags.space || start->flags.plus || start->neg));
		start->flags.zero = 1;
	}
	if (!start->min_width)
		total_len -= ((start->zero_prec && !start->arg)) ? 1 : 0;
	if (start->neg && start->flags.zero)
		write(1, "-", 1);
	(start->flags.minus) ? signed_minus(start, p, printed) :
	signed_unminus(start, p, printed, total_len);
	return (total_len);
}
