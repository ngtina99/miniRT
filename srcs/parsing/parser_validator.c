/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 09:25:33 by yioffe            #+#    #+#             */
/*   Updated: 2024/11/20 16:08:09 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	validator_rgb_end(char *line)
{
	int	count;

	count = 0;
	while (*line)
	{
		while (is_valid_separator(*line))
			line++;
		if (*line == '\0')
			break ;
		if (!ft_isdigit(*line) || ft_atoi(line) < 0 || ft_atoi(line) > 255)
			return (false);
		count++;
		while (ft_isdigit(*line))
			line++;
		if (*line == ',')
		{
			line++;
			if (count == 3)
				return (false);
		}
		else if (!is_valid_separator(*line) && *line != '\0')
			return (false);
	}
	return (count == 3);
}

bool	validator_float_with_range_inline(char **line, float min, float max)
{
	float	result;
	int		point_count;
	int		is_negative;
	char	*start;

	while (is_valid_separator(**line))
		(*line)++;
	is_negative = 0;
	if (**line == '+' || **line == '-')
	{
		if (**line == '-')
			is_negative = 1;
		(*line)++;
	}
	start = *line;
	if (!ft_isdigit(**line))
		return (false);
	point_count = 0;
	while (ft_isdigit(**line) || **line == '.')
	{
		if (**line == '.')
		{
			point_count++;
			if (point_count > 1)
				return (false);
		}
		(*line)++;
	}
	if (*line == start)
		return (false);
	result = parse_float(&start);
	if (is_negative)
		result = -result;
	if (result < min || result > max)
		return (false);
	if (!is_valid_separator(**line) && **line != ',' && **line != '\0')
	{
		printf("Unexpected character after number: '%c'\n", **line);
		return (false);
	}
	return (true);
}

bool	validator_vector3d_with_range(char **line, float min, float max)
{
	if (!validator_float_with_range_inline(line, min, max))
		return (printf("X coordinate of vector is out of range [%f, %f]\n", min,
				max), false);
	if (**line != ',')
		return (printf("Expected ',' after x coordinate in vector\n"), false);
	(*line)++;
	if (!validator_float_with_range_inline(line, min, max))
		return (printf("Y coordinate of vector is out of range [%f, %f]\n", min,
				max), false);
	if (**line != ',')
		return (printf("Expected ',' after y coordinate in vector\n"), false);
	(*line)++;
	if (!validator_float_with_range_inline(line, min, max))
		return (printf("Z coordinate of vector is out of range [%f, %f]\n", min,
				max), false);
	if (!is_valid_separator(**line) && **line != '\0')
		return (printf("Unexpected character after vector: '%c'\n", **line),
			false);
	return (true);
}

bool	validator_fov(char **line)
{
	if (!validator_float_with_range_inline(line, 0.0, 180.0))
	{
		printf("FOV is not valid or out of range.\n");
		return (false);
	}
	while (ft_isdigit(**line) || **line == '.')
		(*line)++;
	while (is_valid_separator(**line))
		(*line)++;
	if (**line != '\0')
	{
		printf("Unexpected characters at the end of FOV: '%s'\n", *line);
		return (false);
	}
	return (true);
}
