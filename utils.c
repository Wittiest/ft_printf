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

int		arg_putchar(char **fmt, va_list *args, t_modifiers *flag_list)
{
	unsigned char	c;
	wint_t			i;

	(*fmt)++;
	if ((*flag_list).flag == L_FLAG)
	{
		i = (wint_t)va_arg(*args, int);
		return(write(1, &i, 1));
	}
	else
	{
		c = (unsigned char)va_arg(*args, int);
		return(write(1, &c, 1));
	}
}

int		arg_putstr(char **fmt, va_list *args, t_modifiers *flag_list)
{
	int i;
	char *s;

	i = 0;
	s = (char *)va_arg(*args, void *);
	if ((*flag_list).flag == L_FLAG)
		i = 0; // Put actual stuff here later.
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	(*fmt)+= i + 2;
	return (i);
}

// static void	ft_putchar(char c)
// {
// 	write(1, &c, 1);
// }

// void	arg_putnbr(char **fmt, va_list *args, t_modifiers *flag_list)
// {
// 	int n;

// 	n = va_arg(*args, int);
// 	if (n == -2147483648)
// 	{
// 		ft_putchar('-');
// 		ft_putchar('2');
// 		ft_putnbr(147483648);
// 		return ;
// 	}
// 	if (n < 0)
// 	{
// 		ft_putchar('-');
// 		n = -n;
// 	}
// 	if (n >= 10)
// 	{
// 		ft_putnbr(n / 10);
// 		ft_putnbr(n % 10);
// 	}
// 	else
// 		ft_putchar(n + '0');
// }

// int		ft_atoi(const char *str)
// {
// 	int		fml[3];

// 	fml[0] = 0;
// 	fml[1] = 0;
// 	fml[2] = 1;
// 	while (*str == ' ' || *str == '\t' || *str == '\r' || *str == '\v' ||
// 		*str == '\n' || *str == '\f')
// 		str++;
// 	if (*str == '+')
// 		str++;
// 	else if (*str == '-' && str++)
// 		fml[2] = -fml[2];
// 	while ('9' >= str[fml[0]] && str[fml[0]] >= '0')
// 		fml[1] = (fml[1] * 10) + str[fml[0]++] - '0';
// 	if (fml[2] == -1)
// 		fml[1] = -fml[1];
// 	return (fml[1]);
// }

// size_t	ft_strlen(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (*(s + i))
// 		i++;
// 	return (i);
// }

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
