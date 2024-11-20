/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validator_scene.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:50:53 by yioffe            #+#    #+#             */
/*   Updated: 2024/11/20 16:10:13 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	validator_sphere(char *line)
{
	if (ft_strncmp(line, "sp", 2) != 0)
		return (false);
	line += 2;
	if (!is_valid_separator(*line))
		return (false);
	while (is_valid_separator(*line))
		line++;
	if (!validator_vector3d_with_range(&line, -(WIDTH + HEIGHT) * 5, (WIDTH
				+ HEIGHT) * 5))
		return (false);
	while (is_valid_separator(*line))
		line++;
	if (!validator_float_with_range_inline(&line, 0, (WIDTH + HEIGHT) * 5))
		return (false);
	while (is_valid_separator(*line))
		line++;
	return (validator_rgb_end(line));
}

bool	validator_cylinder(char *line)
{
	if (ft_strncmp(line, "cy", 2) != 0)
		return (false);
	line += 2;
	if (!is_valid_separator(*line))
		return (false);
	while (is_valid_separator(*line))
		line++;
	if (!validator_vector3d_with_range(&line, -(WIDTH + HEIGHT) * 5, (WIDTH
				+ HEIGHT) * 5))
		return (false);
	while (is_valid_separator(*line))
		line++;
	if (!validator_vector3d_with_range(&line, -1.0, 1.0))
		return (false);
	while (is_valid_separator(*line))
		line++;
	if (!validator_float_with_range_inline(&line, 0, (WIDTH + HEIGHT) * 5))
		return (false);
	while (is_valid_separator(*line))
		line++;
	if (!validator_float_with_range_inline(&line, 0, (WIDTH + HEIGHT) * 5))
		return (false);
	return (validator_rgb_end(line));
}

bool	validator_plane(char *line)
{
	if (ft_strncmp(line, "pl", 2) != 0)
		return (false);
	line += 2;
	if (!is_valid_separator(*line))
		return (false);
	while (is_valid_separator(*line))
		line++;
	if (!validator_vector3d_with_range(&line, -(WIDTH + HEIGHT) * 2, (WIDTH
				+ HEIGHT) * 2))
		return (false);
	while (is_valid_separator(*line))
		line++;
	if (!validator_vector3d_with_range(&line, -1.0, 1.0))
		return (false);
	while (is_valid_separator(*line))
		line++;
	return (validator_rgb_end(line));
}
