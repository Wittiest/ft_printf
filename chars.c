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

	if (start->l_mod == L)
		return(write(1, &start->u_arg, 1));
	else
	{
		c = (char)start->u_arg;
		return(write(1, &c, 1));
	}
}

static int		ft_putstr_wide(wchar_t *str)
{
	int i;

	i = 0;
	if (!str)
		return (write(1, "(null)", 6));
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

static int		ft_putstrr(char *str)
{
	int		i;
	char	c;

	i = 0;
	if (!str)
		return (write(1, "(null)", 6));
	while (str[i])
	{
		c = (char)str[i];
		write(1, &c, 1);
		i++;
	}
	return (i);
}

int		ft_putstr_arg(t_start *start)
{
	if (start->l_mod == L)
		return(ft_putstr_wide((wchar_t *)start->u_arg));
	else
		return(ft_putstrr((char *)start->u_arg));
}