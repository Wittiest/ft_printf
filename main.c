/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpearson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 11:31:22 by dpearson          #+#    #+#             */
/*   Updated: 2017/10/24 11:36:26 by dpearson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <locale.h>

int		main(void)
{
 //    char *locale;
		char *x;
 //    locale = setlocale(LC_ALL, "");	
	// ft_printf("%lc", 266); Not converting :(
    ft_printf("My pointer's address is %p hi hi", (void *)&x);
	return (0);
}
