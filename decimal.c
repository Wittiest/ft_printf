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

	if (start->length_mod == H)
		start->arg = (short)start->arg;
	if (start->length_mod == HH)
		start->arg = (signed char)start->arg;
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
		neg+= write(1, "+", 1);	
	while (--i >= 0)
		neg += write(1, &str[i], 1);
	return (neg);
}

int		unsigned_arg(t_start *start)
{
	char	str[100];
	int		i;
	int		j;

	i = 0;
	if (!start->u_arg && ++i)
		str[0] = '0';
	if (start->length_mod == H)
		start->u_arg = (unsigned short)start->u_arg;
	if (start->length_mod == HH)
		start->arg = (unsigned char)start->u_arg;
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
