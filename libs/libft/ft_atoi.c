/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leanor <leanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:03:23 by yioffe            #+#    #+#             */
/*   Updated: 2024/01/26 12:15:49 by leanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(char c)
{
	return (c == 32 || (c > 8 && c < 14));
}

static int	is_sign(char c)
{
	return (c == 45 || c == 43);
}

int	ft_atoi(const char *str)
{
	int		sign;
	int		number;

	while (is_space(*str))
		str ++;
	sign = 1;
	if (is_sign(*str))
	{
		if (*str == '-')
			sign = sign * (-1);
		str ++;
	}
	number = 0;
	while (ft_isdigit(*str))
	{
		number = 10 * number + (*str - '0');
		str ++;
	}
	return (sign * number);
}
