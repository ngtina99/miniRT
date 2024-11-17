/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 23:21:26 by yioffe            #+#    #+#             */
/*   Updated: 2024/11/16 23:32:41 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	allocate_initial_array(void **array, int *capacity, size_t form_size)
{
	*capacity = INITIAL_CAPACITY;
	*array = malloc(form_size * (*capacity));
	if (!*array)
		return (perror("Error allocating memory"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	resize_array(void **array, int *capacity, int count, size_t form_size)
{
	void	*new_array;
	int		i;

	new_array = malloc(form_size * (*capacity) * 2);
	if (!new_array)
		return (perror("Error allocating memory"), EXIT_FAILURE);
	i = 0;
	while (i < count)
	{
		ft_memcpy((char *)new_array + i * form_size, (char *)(*array) + i
			* form_size, form_size);
		i++;
	}
	free(*array);
	*array = new_array;
	*capacity *= 2;
	return (EXIT_SUCCESS);
}

void	skip_whitespace(char **line)
{
	while (**line == ' ')
		(*line)++;
}

void	skip_invalid_chars(char **line)
{
	while (**line && **line != ' ' && !ft_isdigit(**line) && **line != ','
		&& **line != '.')
		(*line)++;
}
