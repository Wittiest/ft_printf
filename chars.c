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
	wchar_t		*tmp;

	tmp = str;
	if (!str)
		return (write(1, "(null)", 6));
	while (*str)
		str++;
	return(write(1, &str[0], str-tmp));
}

static int		ft_putstrr(char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (write(1, "(null)", 6));
	while (str[i])
		i++;
	return(write(1, &str[0], i));
}

// static	int		ft_str_count(t_start *start)
// {
// 	int		len;
// 	char	*str;
// 	wchar_t	*w_str;

// 	len = 0;
// 	if (start->l_mod == L)
// 	{
// 		w_str = (wchar_t *)start->u_arg;
// 		if (!w_str)
// 			return (6);
// 		while (w_str[len])
// 			len++;
// 	}
// 	else
// 	{
// 		str = (char *)start->u_arg;
// 		if (!str)
// 			return (6);
// 		while (str[len])
// 			len++;
// 	}
// 	return (len);
// }

int		ft_putstr_arg(t_start *start)
{

	if (start->l_mod == L)
		return(ft_putstr_wide((wchar_t *)start->u_arg));
	else
		return(ft_putstrr((char *)start->u_arg));
}