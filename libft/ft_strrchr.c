/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leanor <leanor@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:15:37 by yioffe            #+#    #+#             */
/*   Updated: 2024/01/26 12:19:11 by leanor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	if ((char) c == '\0')
		return ((char *)(s + i));
	i --;
	while (i >= 0)
	{
		if (s[i] == (char) c)
			return ((char *)(s + i));
		i --;
	}
	return (NULL);
}
