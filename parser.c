/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpearson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 19:08:18 by dpearson          #+#    #+#             */
/*   Updated: 2017/12/22 19:08:19 by dpearson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	parse_flags(t_start *start, int *i)
{
	zero_flags(start);
	while (start->format[*i])
	{
		if (start->format[*i] == '#')
			start->flags.hash = 1;
		else if (start->format[*i] == '0')
			start->flags.zero = 1;
		else if (start->format[*i] == '-')
			start->flags.minus = 1;
		else if (start->format[*i] == '+')
			start->flags.plus = 1;
		else if (start->format[*i] == ' ')
			start->flags.space = 1;
		else
			break ;
		(*i)++;
	}
}

static void	parse_field_width(t_start *start, int *i)
{
	start->min_width = 0;
	while (start->format[*i] && (start->format[*i] >= '0') &&
		(start->format[*i] <= '9'))
	{
		start->min_width *= 10;
		start->min_width += (start->format[*i] - '0');
		(*i)++;
	}
}

/*
**	start->zero_prec is used to store difference between no precision and 0
**	precision
*/

static void	parse_prec(t_start *start, int *i)
{
	start->prec = 0;
	if (start->format[*i] == '.')
	{
		(*i)++;
		if (!((start->format[*i] >= '0') && (start->format[*i] <= '9')) ||
			(start->format[*i] == '0'))
			start->zero_prec = 1;
		while (start->format[*i] && (start->format[*i] >= '0') &&
			(start->format[*i] <= '9'))
		{
			start->prec *= 10;
			start->prec += start->format[*i] - '0';
			(*i)++;
		}
	}
	else if (start->format[*i] == '*')
	{
		(*i)++;
		start->prec = va_arg(start->args, int);
	}
}

static void	parse_length_mod(t_start *start, int *i)
{
	if (start->format[*i] == 'z' && (*i)++)
		start->l_mod = Z;
	else if (start->format[*i] == 'j' && (*i)++)
		start->l_mod = J;
	else if (start->format[*i] == 'l')
	{
		(*i)++;
		if (start->format[*i] == 'l' && (*i)++)
			start->l_mod = LL;
		else
			start->l_mod = L;
	}
	else if (start->format[*i] == 'h')
	{
		(*i)++;
		if (start->format[*i] == 'h' && (*i)++)
			start->l_mod = HH;
		else
			start->l_mod = H;
	}
}

void		parser(t_start *start)
{
	int i;
	int ix;

	i = 0;
	ix = 0;
	while (start->format[i])
	{
		start->l_mod = 0;
		if (start->format[i] == '%' || (i++ && 0))
		{
			printstr(ix, i++, start);
			parse_flags(start, &i);
			parse_field_width(start, &i);
			parse_prec(start, &i);
			if (escape_check(start, &i) && (ix = i))
				continue ;
			parse_length_mod(start, &i);
			start->c = start->format[i++];
			start->plus_done = 0;
			parse_conv_char(start);
			ix = i;
		}
	}
	printstr(ix, i, start);
}
