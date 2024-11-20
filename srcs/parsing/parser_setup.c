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

int	parse_ambient(t_data *scene, char *line)
{
	t_ambient	ambient;

	if (!validator_ambient(line))
	{
		ft_putstr_fd("Error\nAmbient format is wrong\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	line++;
	ambient.ratio = parse_float(&line);
	parse_rgb(&line, &ambient.color);
	scene->ambient = ambient;
	scene->ambient_set = true;
	return (EXIT_SUCCESS);
}

int	parse_camera(t_data *scene, char *line)
{
	t_camera	camera;

	if (!validator_camera(line))
	{
		ft_putstr_fd("Wrong camera params\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	line++;
	parse_vector(&line, &camera.position);
	parse_vector(&line, &camera.orientation);
	camera.fov = (int)parse_float(&line);
	scene->camera = camera;
	scene->camera_set = true;
	return (EXIT_SUCCESS);
}

int	parse_light(t_data *scene, char *line)
{
	t_light	light;

	if (!validator_light(line))
	{
		ft_putstr_fd("Wrong light params\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	line++;
	parse_vector(&line, &light.position);
	light.brightness = parse_float(&line);
	parse_rgb(&line, &light.color);
	scene->light = light;
	scene->light_set = true;
	return (EXIT_SUCCESS);
}
