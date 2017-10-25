/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpearson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 03:13:14 by dpearson          #+#    #+#             */
/*   Updated: 2017/10/22 03:16:32 by dpearson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

s_modifiers		*m_head;

void	add_token(s_modifiers *node)
{
	s_modifiers *temp_head;

	temp_head = m_head;
	while (temp_head->next)
		temp_head = temp_head->next;
	temp_head->next = node;
}

size_t	next_token(char *str)
{
	size_t i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '%' && !(str[i + 1] && str[i + 1] == '%'))
			return (i);	
		i++;
	}
	return (0);
}

int		token_count(char *str)
{
	char *segment;
	int count;
	int i;
	size_t next;

	count = 0;
	while (*str)
	{
		next = next_token(*str);
		segment = ft_strndup(str, next); // string up to %
		str+= next + 1;
		count++;
	}
}

void	ft_printf(char *format, ...)
{
	va_list args;
	int t_count;

	t_count = token_count(format);
	va_start (args, t_count);

	// write until %
	// check for modifiers until reaching a conversion char.
	// check argument that matches.
	// write
	// write until next % or end
}
