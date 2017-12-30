/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_prefix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpearson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 19:14:18 by dpearson          #+#    #+#             */
/*   Updated: 2017/12/29 19:14:26 by dpearson         ###   ########.fr       */
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
/*
# 0044 (int)
  ft_printf("%#08x", 42);
  1. (    8) -->00000x2a<--
  2. (    8) -->0x00002a<--
  */