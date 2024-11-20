/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 23:22:29 by yioffe            #+#    #+#             */
/*   Updated: 2024/11/20 14:48:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	parse_sphere(t_data *scene, char *line)
{
	t_sphere			sphere;
	t_add_form_params	params;

	if (!validator_sphere(line))
	{
		ft_putstr_fd("Error\nSphere format is wrong\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
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

	if (!validator_plane(line))
	{
		ft_putstr_fd("Error\nPlane format is wrong\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
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

	if (!validator_cylinder(line))
	{
		ft_putstr_fd("Error\nCylinder format is wrong\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
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
