/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 23:22:29 by yioffe            #+#    #+#             */
/*   Updated: 2024/11/20 14:39:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool validator_shape_size(char **line, float min, float max)
{
    float result;
    int point_count = 0;
    int is_negative = 0;
    char *start;

    while (is_valid_separator(**line))
        (*line)++;
    if (**line == '+' || **line == '-')
	{
        if (**line == '-')
            is_negative = 1;
        (*line)++;
    }
    start = *line; // Mark the start of the number
    if (!ft_isdigit(**line))
        return (false);
    while (ft_isdigit(**line) || **line == '.')
	{
        if (**line == '.')
		{
            point_count++;
            if (point_count > 1) // Multiple dots are invalid
                return false;
        }
        (*line)++;
    }
    if (*line == start) // No valid digits were parsed
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

bool	validator_sphere(char *line)
{
	while (is_valid_separator(*line))
		line++;
	// if (ft_strcmp(line, "sp") != 0) //TODO quit if it is more than sp for exmple spp
	// 	return (false);
	line += 2;
	while (is_valid_separator(*line))
		line++;
	if (!validator_vector3d_with_range(&line, -(WIDTH + HEIGHT) * 2, (WIDTH + HEIGHT) * 2))
		return (false);
	while (is_valid_separator(*line))
		line++;
	if (!validator_shape_size(&line, -(WIDTH + HEIGHT) * 2, (WIDTH + HEIGHT) * 2)); // TODO: function here the float inside max min 
		return (false);
	while (is_valid_separator(*line))
		line++;
	return (validator_rgb_end(line));
}

bool	validator_cylinder(char *line)
{
	while (is_valid_separator(*line))
		line++;
	// if (ft_strcmp(line, "cy") != 0)
	// 	return (false);
	line += 2;
	while (is_valid_separator(*line))
		line++;
	if (!validator_vector3d_with_range(&line, -(WIDTH + HEIGHT) * 2, (WIDTH + HEIGHT) * 2))
		return (false);
	while (is_valid_separator(*line))
		line++;
	if (!validator_vector3d_with_range(&line, -1.0, 1.0))
		return (false);
	while (is_valid_separator(*line))
		line++;
	if (!validator_float_with_range_inline(&line, -(WIDTH + HEIGHT) * 2, (WIDTH + HEIGHT) * 2)); // TODO: function here the float inside max min 
		return (false);
	while (is_valid_separator(*line))
		line++;
	if (!validator_float_with_range_inline(&line, -(WIDTH + HEIGHT) * 2, (WIDTH + HEIGHT) * 2)); // TODO: function here the float inside max min 
		return (false);
	return (validator_rgb_end(line));	
}

bool	validator_plane(char *line)
{
	while (is_valid_separator(*line))
		line++;
	// if (ft_strcmp(line, "pl") != 0)
	// 	return (false);
	line += 2;
	while (is_valid_separator(*line))
		line++;
	if (!validator_vector3d_with_range(&line, -(WIDTH + HEIGHT) * 2, (WIDTH + HEIGHT) * 2)) 
		return (false);
	while (is_valid_separator(*line))
		line++;
	if (!validator_vector3d_with_range(&line, -1.0, 1.0))
		return (false);
	while (is_valid_separator(*line))
		line++;
	return (validator_rgb_end(line));
}
