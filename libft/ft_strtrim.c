/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 18:00:48 by yioffe            #+#    #+#             */
/*   Updated: 2024/05/14 15:46:42 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_in_str(const char *str, char c)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == c)
			return (1);
		str ++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	begin;
	size_t	end;
	size_t	res_len;
	char	*res;

	if (!s1 || !set)
		return (NULL);
	begin = 0;
	end = ft_strlen(s1) - 1;
	while (s1[begin] && char_in_str(set, s1[begin]))
		begin ++;
	if (!s1[begin])
		return (ft_strdup(""));
	while (s1[end] && char_in_str(set, s1[end]))
		end --;
	res_len = end - begin + 1;
	res = (char *)malloc(res_len + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1 + begin, res_len + 1);
	return (res);
}
