/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leanor <leanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 17:40:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/01/26 12:17:30 by leanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_ptr;
	unsigned char	ch;
	size_t			i;

	s_ptr = (unsigned char *)s;
	ch = (unsigned char)c;
	i = 0;
	if (n == 0)
		return (NULL);
	while (i < n)
	{
		if ((unsigned char)s_ptr[i] == ch)
			return (s_ptr + i);
		i ++;
		if (ch == '\0' && i < n && (unsigned char)s_ptr[i] == '\0')
			return (s_ptr + i);
	}
	return (NULL);
}
