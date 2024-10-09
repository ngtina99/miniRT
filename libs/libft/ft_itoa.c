/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leanor <leanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 19:57:38 by yioffe            #+#    #+#             */
/*   Updated: 2024/01/26 12:16:11 by leanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int n)
{
	int	digits;

	if (n == 0)
		return (1);
	digits = 0;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		n *= -1;
		digits ++;
	}
	while (n != 0)
	{
		digits ++;
		n = n / 10;
	}
	return (digits);
}

static void	write_num(char *res, int n, int digits)
{
	int	sign;

	sign = 1;
	if (n < 0)
	{
		res[0] = '-';
		n *= -1;
		sign = -1;
	}
	res[digits] = '\0';
	while (digits > 0)
	{
		digits --;
		res[digits] = (n % 10) + '0';
		n = n / 10;
	}
	if (sign < 0)
		res[0] = '-';
}

char	*ft_itoa(int n)
{
	int		digits;
	char	*res;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	digits = count_digits(n);
	res = (char *)malloc(digits + 1);
	if (!res)
		return (NULL);
	write_num(res, n, digits);
	return (res);
}
