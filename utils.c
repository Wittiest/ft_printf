/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpearson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 19:16:34 by dpearson          #+#    #+#             */
/*   Updated: 2017/12/22 19:16:50 by dpearson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	fix_prefix(t_start *start)
{
	if (start->zero_prec && (start->c == 'O' || start->c == 'o'))
	{
		if (start->flags.hash)
		{
			start->ret += write(1, "0", 1);
			start->flags.hash = 0;
		}
	}
	else if (start->flags.zero && start->flags.hash && start->min_width)
	{
		if (start->min_width)
			start->min_width -= 2;
		if (start->c == 'x')
			start->ret += write(1, "0x", 2);
		if (start->c == 'X')
			start->ret += write(1, "0X", 2);
		start->flags.hash = 0;
	}
}

size_t	unsigned_count(uintmax_t n, int base)
{
	size_t len;

	len = 0;
	while (++len && (n / base))
		n /= base;
	return (len);
}

int		signed_count(intmax_t n)
{
	int	len;

	len = 0;
	while (++len && (n / 10))
		n /= 10;
	return (len);
}

int		escape_check(t_start *start, int *i)
{
	if (start->format[*i] == '%')
	{
		if (!(start->flags.minus) && start->min_width)
		{
			while (--start->min_width > 0)
				start->ret += write(1, " ", 1);
		}
		(*i) += write(1, "%", 1);
		start->ret++;
		if (start->flags.minus && start->min_width)
		{
			while (--start->min_width > 0)
				start->ret += write(1, " ", 1);
		}
		return (1);
	}
	return (0);
}

void	printstr(int begin, int end, t_start *start)
{
	start->ret += write(1, (start->format) + begin, end - begin);
}

void	zero_flags(t_start *start)
{
	start->flags.hash = 0;
	start->flags.zero = 0;
	start->flags.plus = 0;
	start->flags.minus = 0;
	start->flags.space = 0;
	start->neg = 0;
}
