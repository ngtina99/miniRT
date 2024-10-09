/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:17:46 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/08 19:35:14 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	if (!s1 || !s2)
	{
		ft_putstr_nl("one of strings in strcmp is empty", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (n == 0)
		return (0);
	while (*s1 == *s2 && *s1 != '\0' && n > 1)
	{
		s1 ++;
		s2 ++;
		n --;
	}
	return ((unsigned char)(*s1) - (unsigned char)(*s2));
}
