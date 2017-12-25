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

void	escape_check(t_start *start, int *i)
{
	if (start->format[*i] == '%')
		(*i) += write(1, "%", 1);
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
}
