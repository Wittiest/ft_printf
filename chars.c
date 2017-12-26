/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chars.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpearson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 10:46:01 by dpearson          #+#    #+#             */
/*   Updated: 2017/12/25 10:46:02 by dpearson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_putchar_arg(t_start *start)
{
	char	c;

	if (start->length_mod == L)
		return(write(1, &start->u_arg, 1));
	else
	{
		c = (char)start->u_arg;
		return(write(1, &c, 1));
	}
}

int		ft_putstr_arg(t_start *start)
{
	int		i;
	char	c;
	char	*str;

	str = (char *)start->u_arg;
	i = 0;
	if (start->length_mod == L)
	{
		while (str[i])
		{
			write(1, &str[i], 1);
			i++;
		}
	}
	else
	{
		while (str[i])
		{
			c = (char)str[i];
			write(1, &c, 1);
			i++;
		}
	}
	return (i);
}
