/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpearson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 12:23:00 by dpearson          #+#    #+#             */
/*   Updated: 2017/10/24 12:26:24 by dpearson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char *ptr;

	ptr = (unsigned char *)b;
	if (len == 0)
		return (b);
	while (len--)
		*(ptr + len) = (unsigned char)c;
	return (b);
}

char	*ft_strnew(size_t size)
{
	char*str;

	str = (char *)malloc((size + 1) * sizeof(char));
	if (str)
	{
		ft_memset(str, '\0', size + 1);
		return (str);
	}
	return (NULL);
}

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	char *save;

	save = dst;
	while (*src && len)
	{
		*dst = *src;
		dst++;
		src++;
		len--;
	}
	while (len)
	{
		*dst = '\0';
		dst++;
		len--;
	}
	return (save);
}

char	*ft_strndup(const char *s1, size_t n)
{
	char*tmp;

	if (!(tmp = ft_strnew(n)))
		return (NULL);
	ft_strncpy(tmp, s1, n);
	return (tmp);
}
