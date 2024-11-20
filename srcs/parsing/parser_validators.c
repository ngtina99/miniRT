/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validators.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 09:25:33 by yioffe            #+#    #+#             */
/*   Updated: 2024/11/20 11:22:14 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	is_valid_end(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ' || c == '\0');
}

bool	is_valid_separator(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

bool	validator_rgb_end(char *line)
{
	int		value;
	int		count;

	count = 0;
	while (*line)
	{
		while (is_valid_separator(*line))
			line++;
		if (*line == '\0')
			break;
		if (!ft_isdigit(*line))
			return (false);
		value = ft_atoi(line);
		if (value < 0 || value > 255)
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
		else if (!is_valid_end(*line))
			return (false);
	}
	return (count == 3);
}


bool	validator_float_with_range_inline(char **line, float min, float max)
{
	float	result;
	int		point_count;
	char	*start;

	while (is_valid_separator(**line))
		(*line)++;
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
	if (result < min || result > max)
		return (false);

	if (!is_valid_separator(**line) && **line != ',' && **line != '\0')
	{
		printf("Unexpected character after number: '%c'\n", **line);
		return (false);
	}
	return (true);
}

bool	validator_ratio_inline(char **line)
{
	return (validator_float_with_range_inline(line, 0.0, 1.0));
}

bool	validator_float_inline(char **line)
{
	return (validator_float_with_range_inline(line, -FLT_MAX, FLT_MAX));
}

bool	validator_vector3d(char **line)
{
	if (!validator_float_inline(line))
		return (false);
	if (**line != ',')
	{
		printf("Expected ',' after x coordinate\n");
		return (false);
	}
	(*line)++;
	if (!validator_float_inline(line))
		return (false);
	if (**line != ',')
	{
		printf("Expected ',' after y coordinate\n");
		return (false);
	}
	(*line)++;
	if (!validator_float_inline(line))
		return (false);
	return (true);
}

bool	validator_vector3d_normalized(char **line)
{
	float	x, y, z;

	if (!validator_float_with_range_inline(line, -1.0, 1.0))
	{
		printf("X coordinate of vector is out of range [-1.0, 1.0]\n");
		return (false);
	}
	if (**line != ',')
	{
		printf("Expected ',' after x coordinate in vector\n");
		return (false);
	}
	(*line)++;
	if (!validator_float_with_range_inline(line, -1.0, 1.0))
	{
		printf("Y coordinate of vector is out of range [-1.0, 1.0]\n");
		return (false);
	}
	if (**line != ',')
	{
		printf("Expected ',' after y coordinate in vector\n");
		return (false);
	}
	(*line)++;
	if (!validator_float_with_range_inline(line, -1.0, 1.0))
	{
		printf("Z coordinate of vector is out of range [-1.0, 1.0]\n");
		return (false);
	}
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

bool	validator_ambient(char *line)
{
	while (is_valid_separator(*line))
		line++;
	if (*line != 'A')
		return (false);
	line++;
	while (is_valid_separator(*line))
	{
		line++;
	}
	if (!validator_ratio_inline(&line))
		return (false);
	while (is_valid_separator(*line))
		line++;
	return (validator_rgb_end(line));
}

bool	validator_camera(char *line)
{
	while (is_valid_separator(*line))
		line++;
	if (*line != 'C')
		return (false);
	line++;
	while (is_valid_separator(*line))
		line++;
	if (!validator_vector3d(&line))
		return (false);
	while (is_valid_separator(*line))
		line++;
	if (!validator_vector3d_normalized(&line))
		return (false);
	while (is_valid_separator(*line))
		line++;
	if (!validator_fov(&line))
		return (false);
	while (is_valid_separator(*line))
		line++;
	if (*line != '\0')
	{
		printf("Unexpected characters at the end of line: '%s'\n", line);
		return (false);
	}
	return (true);
}




