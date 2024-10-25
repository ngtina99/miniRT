/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 19:04:57 by yioffe            #+#    #+#             */
/*   Updated: 2024/10/24 12:03:51 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*p_dest;
	unsigned char	*p_src;

	p_dest = (unsigned char *)dest;
	p_src = (unsigned char *)src;
	if ((uintptr_t)p_dest + n < (uintptr_t)p_dest || (uintptr_t)p_src
		+ n < (uintptr_t)p_src)
		return (NULL);
	if (p_dest > p_src && p_dest < p_src + n)
	{
		p_dest += n - 1;
		p_src += n - 1;
		while (n > 0)
		{
			*p_dest-- = *p_src--;
			n--;
		}
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
