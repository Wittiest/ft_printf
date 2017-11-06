/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpearson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 06:38:31 by dpearson          #+#    #+#             */
/*   Updated: 2017/10/30 19:45:02 by dpearson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int		(*g_funcs[])(va_list *, t_modifiers *) = {arg_putchar, arg_putstr, arg_ptr, x_flag_low, x_flag_upp, arg_dec};
char	g_conversion[15] = "cspxXdCSDioOuU\0";

t_modifiers		*flag_list_init(void)
{
	t_modifiers *flag_list;

	flag_list = malloc(sizeof(t_modifiers));
	*flag_list = (t_modifiers){0, 0, 0, 0, 0, 0, 0, 0};
	return (flag_list);
}

int				find_flags(va_list *args, const char **fmt, t_modifiers *flag_list)
{
	int i;

	while (**fmt)
	{
		i = -1;
		while (g_conversion[++i])
			if (g_conversion[i] == **fmt)
				return(g_funcs[i](args, flag_list));
		if (**fmt >= '0' && **fmt <= '9' && !(*flag_list).min_width)
			(*flag_list).min_width = arg_ft_atoi(fmt);			
		else if (**fmt == '#')
			(*flag_list).hash = 1;
		else if (**fmt == '0')
			(*flag_list).zero = 1;
		else if (**fmt == '-')
			(*flag_list).minus = 1;
		else if (**fmt == '+')
			(*flag_list).plus = 1;
		else if (**fmt == ' ')
			(*flag_list).space = 1;
		else if (**fmt == 'h' && !((*flag_list).flag))
			(*flag_list).flag = (*(*fmt + 1) && (*(*fmt + 1) == 'h')) ? HH_FLAG : H_FLAG;
		else if (**fmt == 'l' !((*flag_list).flag))
			(*flag_list).flag = (*(*fmt + 1) && (*(*fmt + 1) == 'l')) ? LL_FLAG : L_FLAG;
		else if (**fmt == 'j')
			(*flag_list).flag = J_FLAG;
		else if (**fmt == 'z')
			(*flag_list).flag = Z_FLAG;
		(*fmt)++;
	}
	return (-1);
}

int				ft_printf(const char *format, ...)
{
	va_list		args;
	int			char_count;

	va_start(args, format);
	char_count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			if (*(format + 1) && (*(format + 1) == '%') && (format += 2))
				write(1, "%%", 1);
			else
			{
				char_count += find_flags(&args, &format, flag_list_init());
				format++;
			}
		}
		else
		{
			char_count += write(1, format, 1);
			format++;
		}
	}
	va_end(args);
	return (char_count);
}
