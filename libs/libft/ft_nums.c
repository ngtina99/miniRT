/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nums.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:20:15 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/01/27 17:00:13 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putcharptr(unsigned long signvalue)
{
	if (signvalue == 0)
	{
		return (ft_putstr("(nil)"));
	}
	return (ft_putstr("0x") + ft_putptr(signvalue));
}

int	ft_putptr(unsigned long l)
{
	int					i;
	char				*symbols;
	unsigned long		base;

	base = 16;
	symbols = "0123456789abcdef";
	if (l < base)
		return (write(1, &symbols[l], 1));
	else
	{
		i = ft_putptr(l / base);
	}
	i += ft_putptr(l % base);
	return (i);
}

int	ft_putnbr(long n, int base, char type)
{
	int		i;
	char	*lowersymbols;
	char	*uppersymbols;

	lowersymbols = "0123456789abcdef";
	uppersymbols = "0123456789ABCDEF";
	i = 0;
	if (n < 0)
	{
		return (ft_putchar('-') + ft_putnbr(-n, base, type));
	}
	else if (n < base && (type != 'X'))
	{
		return (write(1, &lowersymbols[n], 1));
	}
	else if (n < base && type == 'X')
	{
		return (write(1, &uppersymbols[n], 1));
	}
	else
	{
		i = ft_putnbr(n / base, base, type);
	}
	i += ft_putnbr(n % base, base, type);
	return (i);
}
