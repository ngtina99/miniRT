/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:49:09 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/07 15:29:54 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*empty_arg(char const *dest, char const *src)
{
	if (!dest && !src)
		return (NULL);
	else if (!dest)
		return (ft_strdup(src));
	else if (!src)
		return (ft_strdup(dest));
	else
		return (NULL);
}

char	*ft_strjoin(char const *dest, char const *src)
{
	char	*result;
	char	*start_ptr;
	int		total_size;

	if (!dest || !src)
		return (empty_arg(dest, src));
	total_size = ft_strlen(dest) + ft_strlen(src);
	result = (char *)malloc(total_size + 1);
	if (result == NULL)
		return (NULL);
	start_ptr = result;
	while (*dest != '\0')
	{
		*result = *dest;
		result ++;
		dest ++;
	}
	while (*src != '\0')
	{
		*result = *src;
		result ++;
		src ++;
	}
	*result = '\0';
	return (start_ptr);
}
