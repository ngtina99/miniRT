/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:43:55 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/22 21:25:35 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, int size)
{
	char		*str_new;
	int			i;

	if (!src)
		return (NULL);
	str_new = (char *)malloc(size * sizeof(char) + 1);
	if (str_new == NULL)
		return (NULL);
	i = 0;
	while (src[i] && i < size)
	{
		str_new[i] = src[i];
		i ++;
	}
	str_new[i] = '\0';
	return (str_new);
}
