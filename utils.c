/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpearson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 06:38:36 by dpearson          #+#    #+#             */
/*   Updated: 2017/10/26 11:13:36 by dpearson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <string.h>
#include <stdio.h>

char	g_upp_hex[17] = "0123456789ABCDEF";
char	g_low_hex[17] = "0123456789abcdef";

int		ft_putchar(char c)
{
	return(write(1, &c, 1));
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*(s + i))
		i++;
	return (i);
}

void	write_spaces(int i)
{
	while (i--)
		ft_putchar(' ');
}

int		arg_putchar(va_list *args, t_modifiers *flag_list)
{
	unsigned char	c;

	c = (unsigned char)va_arg(*args, int);
	if ((*flag_list).min_width)
		write_spaces((*flag_list).min_width - 1);
	return((*flag_list).min_width + write(1, &c, 1));
}

int		arg_putstr(va_list *args, t_modifiers *flag_list)
{
	int i;
	int len;
	char *s;

	i = 0;
	s = (char *)va_arg(*args, void *);
	len = ft_strlen((const char *)s);
	if ((*flag_list).min_width > len)
		write_spaces((*flag_list).min_width - len);
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (((*flag_list).min_width) ? (*flag_list).min_width : len);
}

int		print_hex(unsigned int n, int low)
{
	int i;

	i = 0;
	if (n >= 16)
		i = print_hex(n / 16, low);
	if (low)
		write(1, &g_low_hex[n % 16], 1);
	else
		write(1, &g_upp_hex[n % 16], 1);
	return (1 + i);
}

int		x_flag_low(va_list *args, t_modifiers *flag_list)
{
	unsigned int nbr;

	if ((*flag_list).flag == L_FLAG)
		nbr = 0; // Put actual stuff here later.
	nbr = (unsigned int)va_arg(*args, int);
	return (print_hex(nbr, 1));
}

int		x_flag_upp(va_list *args, t_modifiers *flag_list)
{
	unsigned int nbr;

	if ((*flag_list).flag == L_FLAG)
		nbr = 0; // Put actual stuff here later.
	nbr = (unsigned int)va_arg(*args, int);
	return (print_hex(nbr, 0));
}

int		arg_ptr(va_list *args, t_modifiers *flag_list)
{
	unsigned int nbr;

	flag_list = NULL; // fix later
	nbr = (unsigned int)va_arg(*args, void *);
	return (print_hex(nbr, 1));
}

int		ft_putnbr(int nb)
{
	int i;

	i = 0;
	if (nb == -2147483648)
	{
		ft_putchar('-');
		ft_putchar('2');
		return(2 + ft_putnbr(147483648));
	}
	if (nb < 0)
	{
		ft_putchar('-');
		i++;
		nb = -nb;
	}
	if (nb >= 10)
	{
		i+= ft_putnbr(nb / 10);
		i+= ft_putnbr(nb % 10);
	}
	else
	{
		i += ft_putchar(nb + '0');
	}
	return (i);
}

int		arg_dec(va_list *args, t_modifiers *flag_list)
{
	int nbr;

	if ((*flag_list).flag == L_FLAG)
		nbr = 0; // Put actual stuff here later.
	nbr = va_arg(*args, int);
	return (ft_putnbr(nbr));
}

int		arg_ft_atoi(const char **str)
{
	int		neg;
	int		nbr;

	neg = 1;
	nbr = 0;
	while (**str == ' ' || **str == '\t'|| **str == '\v' || **str == '\n')
		(*str)++;
	if (**str == '+')
		(*str)++;
	else if (**str == '-' && (*str)++)
		neg = -1;
	while ('9' >= (**str) && **str >= '0')
	{
		nbr = (nbr * 10) + ((**str) - '0');
		(*str)++;
	}
	(*str)--; // Since the other function always adds
	return (nbr * neg);
}

// void	*ft_memset(void *b, int c, size_t len)
// {
// 	unsigned char *ptr;

// 	ptr = (unsigned char *)b;
// 	if (len == 0)
// 		return (b);
// 	while (len--)
// 		*(ptr + len) = (unsigned char)c;
// 	return (b);
// }

// char	*ft_strnew(size_t size)
// {
// 	char*str;

// 	str = (char *)malloc((size + 1) * sizeof(char));
// 	if (str)
// 	{
// 		ft_memset(str, '\0', size + 1);
// 		return (str);
// 	}
// 	return (NULL);
// }

// char	*ft_strncpy(char *dst, const char *src, size_t len)
// {
// 	char *save;

// 	save = dst;
// 	while (*src && len)
// 	{
// 		*dst = *src;
// 		dst++;
// 		src++;
// 		len--;
// 	}
// 	while (len)
// 	{
// 		*dst = '\0';
// 		dst++;
// 		len--;
// 	}
// 	return (save);
// }

// char	*ft_strndup(const char *s1, size_t n)
// {
// 	char	*tmp;

// 	if (!(tmp = ft_strnew(n)))
// 		return (NULL);
// 	ft_strncpy(tmp, s1, n);
// 	return (tmp);
// }
