/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arsene <Arsene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:49:26 by arurangi          #+#    #+#             */
/*   Updated: 2022/12/07 07:40:03 by Arsene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Prints string to standard output and handles basic format specifiers
*/

#include "libft.h"

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		index;
	int		counter;

	counter = 0;
	va_start(args, str);
	index = 0;
	while (str[index])
	{
		if (str[index] == '%' && str[index + 1])
		{
			ft_putfs(str[index + 1], args, &counter);
			index++;
		}
		else
		{
			ft_putchar(str[index]);
			counter++;
		}
		index++;
	}
	va_end(args);
	return (counter);
}
