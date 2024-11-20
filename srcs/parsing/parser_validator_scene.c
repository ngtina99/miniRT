/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validator_scene.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:50:53 by yioffe            #+#    #+#             */
/*   Updated: 2024/11/20 15:58:26 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	validator_ambient(char *line)
{
	while (is_valid_separator(*line))
		line++;
	if (*line != 'A')
		return (false);
	line++;
	while (is_valid_separator(*line))
		line++;
	if (!validator_float_with_range_inline(&line, 0.0, 1.0))
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
	if (!validator_vector3d_with_range(&line, -(WIDTH + HEIGHT) * 2, (WIDTH
				+ HEIGHT) * 2))
		return (false);
	while (is_valid_separator(*line))
		line++;
	if (!validator_vector3d_with_range(&line, -1.0, 1.0))
		return (false);
	while (is_valid_separator(*line))
		line++;
	if (!validator_fov(&line))
		return (false);
	while (is_valid_separator(*line))
		line++;
	if (*line != '\0')
		return (printf("Unexpected characters at the end of line: '%s'\n",
				line), false);
	return (true);
}

bool	validator_light(char *line)
{
	while (is_valid_separator(*line))
		line++;
	if (*line != 'L')
		return (false);
	line++;
	while (is_valid_separator(*line))
		line++;
	if (!validator_vector3d_with_range(&line, -(WIDTH + HEIGHT) * 2, (WIDTH
				+ HEIGHT) * 2))
		return (false);
	while (is_valid_separator(*line))
		line++;
	if (!validator_float_with_range_inline(&line, 0.0, 1.0))
		return (false);
	while (is_valid_separator(*line))
		line++;
	return (validator_rgb_end(line));
}