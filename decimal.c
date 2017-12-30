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

int		signed_arg(t_start *start)
{
	char	str[100];
	int		neg;
	int		i;
	size_t	p;

	p = signed_count(start->arg, start);
	neg = (start->arg < 0) ? write(1, "-", 1) : 0;
	i = 0;
	if (!start->arg && ++i)
		str[0] = '0';
	while ((start->arg) > 0 || ((neg) && (start->arg < 0)))
	{
		str[i] = '0' + ((neg) ? -(start->arg % 10) : (start->arg % 10));
		start->arg /= 10;
		i++;
	}
	if ((start->flags.space || start->flags.plus) && !neg)
		neg += write(1, (start->flags.plus) ? "+" : " ", 1);
	while (--i >= 0)
		neg += write(1, &str[i], 1);
	return (neg);
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
	int		ret;

	ret = unsigned_count(start->u_arg, 10);
	unsigned_arg(start->u_arg);
	return (ret);
}