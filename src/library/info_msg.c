/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_msg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 09:51:20 by Arsene            #+#    #+#             */
/*   Updated: 2023/01/16 14:34:39 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	info_msg(int return_code, char *message, ...)
{
	va_list	args;
	int		index;

	ft_putstr("\033[34m○\033[0m ");
	va_start(args, message);
	index = 0;
	while (message[index])
	{
		if (message[index] == '%')
		{
			if (message[index + 1] == 's')
				ft_putstr(va_arg(args, char *));
			else if (message[index + 1] == 'd')
				ft_putnbr(va_arg(args, int));
			index++;
		}
		else
			ft_putchar(message[index]);
		index++;
	}
	write(1, "\n", 1);
	return (return_code);
}
