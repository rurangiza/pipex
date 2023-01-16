/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 10:45:54 by arurangi          #+#    #+#             */
/*   Updated: 2023/01/16 11:05:31 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putchar_mod(char c)
{
	write(1, &c, 1);
	return (1);
}

static int	ft_putstr_mod(char *str)
{
	int	i;

	if (!str)
	{
		ft_putstr_mod("(null)");
		return (6);
	}
	i = 0;
	while (str[i] != '\0')
	{
		ft_putchar_mod(str[i]);
		i++;
	}
	return (i);
}

static int	ft_putnbr_mod(int nbr, int *counter)
{
	char	ch;

	if (nbr > 9)
	{
		ft_putnbr_mod((nbr / 10), counter);
		ft_putnbr_mod((nbr % 10), counter);
	}
	else if (nbr == INT_MIN)
	{
		return (ft_putstr_mod("-2147483648") + *counter);
	}
	else if (nbr < 0)
	{
		(*counter)++;
		ft_putchar_mod('-');
		nbr = -nbr;
		ft_putnbr_mod(nbr, counter);
	}
	else if (nbr >= 0 && nbr < 10)
	{
		(*counter)++;
		ch = nbr + '0';
		ft_putchar_mod(ch);
	}
	return (*counter);
}

static int	ft_puthex(unsigned long nbr, char format, int *counter)
{
	char	ch;
	char	*base;

	base = "0123456789abcdef";
	if (nbr > 16 - 1)
	{
		ft_puthex(nbr / 16, format, counter);
		ft_puthex(nbr % 16, format, counter);
	}
	else
	{
		(*counter)++;
		ch = base[nbr];
		if (format == 'X' && ft_isalpha(ch))
			ch -= 32;
		ft_putchar(ch);
	}
	return (*counter);
}

int	ft_putnbr_u(unsigned int nbr, int *counter)
{
	char			ch;

	if (nbr > 9)
	{
		ft_putnbr_u((nbr / 10), counter);
		ft_putnbr_u((nbr % 10), counter);
	}
	else if (nbr >= 0 && nbr < 10)
	{
		(*counter)++;
		ch = nbr + '0';
		ft_putchar(ch);
	}
	return (*counter);
}

void	ft_putfs(char ch, va_list args, int *counter)
{
	if (ch == 'c')
			*counter += ft_putchar_mod(va_arg(args, int));
	else if (ch == 's')
		*counter += ft_putstr_mod(va_arg(args, char *));
	else if (ch == 'i' || ch == 'd')
		*counter = ft_putnbr_mod(va_arg(args, int), counter);
	else if (ch == 'u')
		*counter = ft_putnbr_u(va_arg(args, unsigned int), counter);
	else if (ch == '%')
		*counter += ft_putchar_mod('%');
	else if (ch == 'x' || ch == 'X')
		ft_puthex(va_arg(args, unsigned int), ch, counter);
	else if (ch == 'p')
	{
		ft_putstr_mod("0x");
		ft_puthex(va_arg(args, unsigned long), ch, counter);
		*counter += 2;
	}
}