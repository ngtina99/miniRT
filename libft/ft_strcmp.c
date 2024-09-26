/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:16:35 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/08 19:34:46 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
	{
		ft_putstr_nl("one of strings in strcmp is empty", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	while (*s1 == *s2 && *s1 != '\0')
	{
		s1 ++;
		s2 ++;
	}
	return ((unsigned char)(*s1) - (unsigned char)(*s2));
}
