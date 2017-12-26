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

	neg = (start->arg < 0) ? 1 : 0;
	if (neg)
		write(1, "-", 1);
	if (!start->arg)
		write(1, "0", 1);
	i = 0;
	while ((start->arg) > 0)
	{
		str[i] = '0' + ((neg) ? -(start->arg % 10) : (start->arg % 10));
		start->arg /= 10;
		i++;
	}
	neg = i;
	while (--i >= 0)
		write(1, &str[i], 1);
	return (neg);
}