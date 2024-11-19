/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 23:22:29 by yioffe            #+#    #+#             */
/*   Updated: 2024/11/19 19:22:33 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	parse_sphere(t_data *scene, char *line)
{
	t_sphere			sphere;
	t_add_form_params	params;

	line += 2;
	parse_vector(&line, &sphere.center);
	sphere.diameter = parse_float(&line);
	parse_rgb(&line, &sphere.color);
	params.array = (void **)&scene->spheres;
	params.count = &scene->sphere_count;
	params.capacity = &scene->sphere_capacity;
	params.form_size = sizeof(t_sphere);
	return (add_form(&params, &sphere));
}

int	parse_plane(t_data *scene, char *line)
{
	t_plane				plane;
	t_add_form_params	params;

	line += 2;
	parse_vector(&line, &plane.point);
	parse_vector(&line, &plane.normal);
	parse_rgb(&line, &plane.color);
	params.array = (void **)&scene->planes;
	params.count = &scene->plane_count;
	params.capacity = &scene->plane_capacity;
	params.form_size = sizeof(t_plane);
	return (add_form(&params, &plane));
}

int	parse_cylinder(t_data *scene, char *line)
{
	t_cylinder			cylinder;
	t_add_form_params	params;

	line += 2;
	parse_vector(&line, &cylinder.center);
	parse_vector(&line, &cylinder.axis);
	cylinder.diameter = parse_float(&line);
	cylinder.height = parse_float(&line);
	parse_rgb(&line, &cylinder.color);
	params.array = (void **)&scene->cylinders;
	params.count = &scene->cylinder_count;
	params.capacity = &scene->cylinder_capacity;
	params.form_size = sizeof(t_cylinder);
	return (add_form(&params, &cylinder));
}

int	parse_camera(t_data *scene, char *line)
{
	t_camera	camera;

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

	line++;
	parse_vector(&line, &light.position);
	light.brightness = parse_float(&line);
	parse_rgb(&line, &light.color);
	scene->light = light;
	scene->light_set = true;
	return (EXIT_SUCCESS);
}
