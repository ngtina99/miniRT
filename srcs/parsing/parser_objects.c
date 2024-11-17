/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 23:22:29 by yioffe            #+#    #+#             */
/*   Updated: 2024/11/17 00:19:43 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	parse_sphere(t_data *scene, char *line)
{
	t_sphere	sphere;
	int			result;

	line += 2;
	parse_vector(&line, &sphere.center);
	sphere.diameter = parse_float(&line);
	parse_rgb(&line, &sphere.color);
	return (add_form((void **)&scene->spheres, &scene->sphere_count,
			&scene->sphere_capacity, &sphere, sizeof(t_sphere)));
}

int	parse_plane(t_data *scene, char *line)
{
	t_plane	plane;

	line += 2;
	parse_vector(&line, &plane.point);
	parse_vector(&line, &plane.normal);
	parse_rgb(&line, &plane.color);
	return (add_form((void **)&scene->planes, &scene->plane_count,
			&scene->plane_capacity, &plane, sizeof(t_plane)));
}

int	parse_cylinder(t_data *scene, char *line)
{
	t_cylinder	cylinder;

	line += 2;
	parse_vector(&line, &cylinder.center);
	parse_vector(&line, &cylinder.axis);
	cylinder.diameter = parse_float(&line);
	cylinder.height = parse_float(&line);
	parse_rgb(&line, &cylinder.color);
	return (add_form((void **)&scene->cylinders, &scene->cylinder_count,
			&scene->cylinder_capacity, &cylinder, sizeof(t_cylinder)));
}

int	parse_camera(t_data *scene, char *line)
{
	t_camera	camera;

	line++;
	parse_vector(&line, &camera.position);
	parse_vector(&line, &camera.orientation);
	camera.fov = (int)parse_float(&line);
	scene->camera = camera;
	return (EXIT_SUCCESS);
}

int	parse_light(t_data *scene, char *line)
{
	t_light	light;

	line++;
	parse_vector(&line, &light.position);
	light.brightness = parse_float(&line);
	parse_rgb(&line, &light.color);
	scene->light = light;
	return (EXIT_SUCCESS);
}
