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
	char	str[100]; // malloc based on total len of #, malloc bigger
	int		neg;
	int		i;
	int		p;

	p = signed_count(start->arg);
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
	if (start->flags.plus && !neg)
		neg += write(1, "+", 1);	
	while (--i >= 0)
		neg += write(1, &str[i], 1);
	return (neg);
}
// externalize length modifiers based on signed and unsigned
int		unsigned_arg(t_start *start)
{
	char	str[100];
	int		i;
	int		j;
	int		p;

	p = unsigned_count(start->u_arg, 10);
	i = 0;
	if (!start->u_arg && ++i)
		str[0] = '0';
	while ((start->u_arg) > 0)
	{
		str[i] = '0' + (start->u_arg % 10);
		start->u_arg /= 10;
		i++;
	}
	j = i;
	while (--i >= 0)
		write(1, &str[i], 1);
	return (j);
}
