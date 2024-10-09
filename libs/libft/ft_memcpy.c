/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leanor <leanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:51:33 by yioffe            #+#    #+#             */
/*   Updated: 2024/01/26 12:17:41 by leanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*p_dest;
	unsigned char	*p_src;
	size_t			i;

	p_dest = (unsigned char *) dest;
	p_src = (unsigned char *) src;
	if (p_dest == NULL && p_src == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		p_dest[i] = p_src[i];
		i ++;
	}
	return (dest);
}
