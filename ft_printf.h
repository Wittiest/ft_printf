/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpearson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 03:16:37 by dpearson          #+#    #+#             */
/*   Updated: 2017/10/26 11:13:52 by dpearson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <wchar.h>
# define HH_FLAG 1
# define H_FLAG 2
# define L_FLAG 3
# define LL_FLAG 4
# define J_FLAG 5
# define Z_FLAG 6

typedef struct			s_modifiers
{
	short				hash;
	short				zero;
	short				minus;
	short				plus;
	short				space;
	int					min_width;
	int					precision;
	short				flag;
}						t_modifiers;

int						ft_printf(char *format, ...);
int						arg_putchar(char **fmt, va_list *args, t_modifiers *flag_list);
int						arg_putstr(char **fmt, va_list *args, t_modifiers *flag_list);
int						arg_ptr(char **fmt, va_list *args, t_modifiers *flag_list);

#endif
