/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpearson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 06:38:31 by dpearson          #+#    #+#             */
/*   Updated: 2017/12/24 12:58:09 by dpearson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int		ft_printf(char *format, ...)
{
	t_start		start;

	start.format = format;
	start.ret = 0;
	va_start(start.args, format);
	parser(&start);
	va_end(start.args);
	return (start.ret);
}
