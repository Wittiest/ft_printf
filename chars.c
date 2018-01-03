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

static void	ft_putstr_wide(t_start *start, wchar_t *str, int strlen, int lim)
{
	int			i;

	if (!(start->flags.minus) && ((lim > strlen) || (lim > start->prec)))
		while ((start->min_width-- > strlen) ||
		((start->prec) && (start->min_width + 1) > start->prec))
			write(1, " ", 1);
	i = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		if ((start->flags.minus) && ((lim > strlen) || (lim > start->prec)))
			while ((start->min_width-- > strlen) || ((start->prec) &&
				(start->min_width + 1) > start->prec))
				write(1, " ", 1);
		return ;
	}
	while ((i < strlen) && (start->prec ? (i < start->prec) : 1))
		write(1, &str[i++], 1);
	if ((start->flags.minus) && ((lim > strlen) || (lim > start->prec)))
		while ((start->min_width-- > strlen) || ((start->prec) &&
			(start->min_width + 1) > start->prec))
			write(1, " ", 1);
}

static void	ft_putstrr(t_start *start, char *str, int strlen, int lim)
{
	int			i;

	if (!(start->flags.minus) && ((lim > strlen) || (lim > start->prec)))
		while ((start->min_width-- > strlen) || ((start->prec) &&
			(start->min_width + 1) > start->prec))
			write(1, " ", 1);
	i = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		if ((start->flags.minus) && ((lim > strlen) || (lim > start->prec)))
			while ((start->min_width-- > strlen) || ((start->prec) &&
				(start->min_width + 1) > start->prec))
				write(1, " ", 1);
		return ;
	}
	while ((i < strlen) && (start->prec ? (i < start->prec) : 1))
		write(1, &str[i++], 1);
	if ((start->flags.minus) && ((lim > strlen) || (lim > start->prec)))
		while ((start->min_width-- > strlen) || ((start->prec) &&
			(start->min_width + 1) > start->prec))
			write(1, " ", 1);
}

static int	ft_str_count(t_start *start)
{
	int		len;
	char	*str;
	wchar_t	*w_str;

	len = 0;
	if (start->l_mod == L)
	{
		w_str = (wchar_t *)start->u_arg;
		if (!w_str)
			return (6);
		while (w_str[len])
			len++;
	}
	else
	{
		str = (char *)start->u_arg;
		if (!str)
			return (6);
		while (str[len])
			len++;
	}
	return (len);
}

int			ft_putstr_arg(t_start *start)
{
	int		count;
	int		limit;
	int		ret;

	limit = (start->prec > start->min_width) ? start->prec : start->min_width;
	count = ft_str_count(start);
	ret = (limit > count) ? limit : count;
	if (start->prec)
	{
		if (start->min_width == 0)
			ret = (start->prec < count) ? start->prec : count;
		else if (start->prec < count)
		{
			if (start->min_width > start->prec)
				ret = start->min_width;
			else
				ret = ((start->min_width) > count) ? (start->min_width) : count;
		}
		else if ((start->prec > start->min_width))
			ret = (start->min_width > count) ? start->min_width : count;
	}
	(start->l_mod == L) ? ft_putstr_wide(start, (wchar_t *)start->u_arg, count,
		limit) : ft_putstrr(start, (char *)start->u_arg, count, limit);
	return (ret);
}

int			ft_putchar_arg(t_start *start)
{
	char		c;
	int			i;
	int			j;

	i = start->min_width;
	j = i;
	if (!(start->flags.minus))
		while (j-- > 1)
			write(1, " ", 1);
	if (start->l_mod == L)
		write(1, &start->u_arg, 1);
	else
	{
		c = (char)start->u_arg;
		write(1, &c, 1);
	}
	if (start->flags.minus)
		while (j-- > 1)
			write(1, " ", 1);
	return ((i) ? i : 1);
}
