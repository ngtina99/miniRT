/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leanor <leanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:05:21 by yioffe            #+#    #+#             */
/*   Updated: 2024/01/26 12:17:54 by leanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t num)
{
	unsigned char	*byte_ptr;
	unsigned char	byte_value;
	size_t			i;

	byte_ptr = ptr;
	byte_value = (unsigned char) value;
	i = 0;
	while (i < num)
	{
		byte_ptr[i] = byte_value;
		i ++;
	}
	return (ptr);
}
