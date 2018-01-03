/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpearson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 07:00:57 by dpearson          #+#    #+#             */
/*   Updated: 2018/01/03 07:01:06 by dpearson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t		unsigned_count(uintmax_t n, int base)
{
	size_t len;

	len = 0;
	while (++len && (n / base))
		n /= base;
	return (len);
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

int			unsigned_arg_handler(t_start *start)
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
