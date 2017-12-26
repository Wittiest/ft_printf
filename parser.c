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
			break;
		(*i)++;
	}
}

static void	parse_field_width(t_start *start, int *i)
{
	start->min_width = 0;
	while (start->format[*i] && (start->format[*i] >= '0') && (start->format[*i] <= '9'))
	{
		start->min_width *= 10;
		start->min_width += (start->format[*i] - '0');
		(*i)++;
	}
}

static void	parse_precision(t_start *start, int *i)
{
	// add handling for *
	start->precision = 0;
	if (start->format[*i] == '.')
	{
		(*i)++;
		while (start->format[*i] && (start->format[*i] >= '0') && (start->format[*i] <= '9'))
		{
			start->precision *= 10;
			start->precision += start->format[*i] - '0';
			(*i)++;
		}
	}
}

static void	parse_length_mod(t_start *start, int *i)
{
	if (start->format[*i] == 'z' && (*i)++)
		start->length_mod = Z;
	else if (start->format[*i] == 'j' && (*i)++)
		start->length_mod = J;
	else if (start->format[*i] == 'l')
	{
		(*i)++;
		if (start->format[*i] == 'l' && (*i)++)
			start->length_mod = LL;
		else
			start->length_mod = L;
	}
	else if (start->format[*i] == 'h')
	{
		(*i)++;
		if (start->format[*i] == 'h' && (*i)++)
			start->length_mod = HH;
		else
			start->length_mod = H;
	}		
}

void		parser(t_start *start)
{
	int i;
	int ix;

	i = ix = 0;
	while (start->format[i])
	{
		if (start->format[i] == '%')
		{
			printstr(ix, i, start);
			i++;
			if (escape_check(start, &i) && (ix = i))
				continue ;
			parse_flags(start, &i);
			parse_field_width(start, &i);
			parse_precision(start, &i);
			parse_length_mod(start, &i);
			start->c = start->format[i++];
			parse_conv_char(start);
			ix = i;
		}
		else
			i++;
	}
	printstr(ix, i, start);
}