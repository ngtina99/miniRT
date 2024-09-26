/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:25:34 by yioffe            #+#    #+#             */
/*   Updated: 2024/03/14 17:26:49 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_linelen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != '\n')
		i++;
	if (str && str[i] == '\n')
		i++;
	return (i);
}

static char	*ft_linejoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	str = (char *)malloc(ft_linelen(s1) + ft_linelen(s2) + 1);
	if (!str)
		return (NULL);
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\n' && s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	if (s2[j] == '\n')
		str[i + j++] = '\n';
	str[i + j] = '\0';
	if (s1)
		free(s1);
	return (str);
}

static void	ft_free_gnl(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\n' && i < BUFFER_SIZE)
	{
		str[i] = '\0';
		i++;
	}
	if (str[i] == '\n')
	{
		str[i] = '\0';
		i++;
		while (i < BUFFER_SIZE)
		{
			str[j] = str[i];
			str[i] = '\0';
			i++;
			j++;
		}
	}
}

char	*get_next_line(int fd)
{
	static char		buffer [FOPEN_MAX][BUFFER_SIZE + 1];
	char			*str;
	int				i;

	i = 0;
	if (read(fd, 0, 0) < 0 || FOPEN_MAX <= fd || BUFFER_SIZE <= 0)
	{
		if (fd > 0 && FOPEN_MAX > fd)
			while (buffer[fd][i])
				buffer[fd][i++] = '\0';
		return (NULL);
	}
	str = NULL;
	while (buffer[fd][0] || read(fd, buffer[fd], BUFFER_SIZE) > 0)
	{
		str = ft_linejoin(str, buffer[fd]);
		ft_free_gnl(buffer[fd]);
		if (str[ft_linelen(str) - 1] == '\n')
			return (str);
	}
	return (str);
}
