/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:46:24 by yioffe            #+#    #+#             */
/*   Updated: 2024/11/20 15:46:24 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	add_form(t_add_form_params *params, void *new_form)
{
	if (*(params->count) == 0)
	{
		if (allocate_initial_array(params->array, params->capacity,
				params->form_size) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (*(params->count) == *(params->capacity))
	{
		if (resize_array(params->array, params->capacity, *(params->count),
				params->form_size) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	ft_memcpy((char *)(*(params->array)) + (*(params->count))
		* params->form_size, new_form, params->form_size);
	(*(params->count))++;
	return (EXIT_SUCCESS);
}

void	initialize_scene(t_data *scene)
{
	scene->spheres = NULL;
	scene->sphere_count = 0;
	scene->sphere_capacity = 0;
	scene->planes = NULL;
	scene->plane_count = 0;
	scene->plane_capacity = 0;
	scene->cylinders = NULL;
	scene->cylinder_count = 0;
	scene->cylinder_capacity = 0;
	scene->ambient_set = false;
	scene->camera_set = false;
	scene->light_set = false;
}

int	handle_global_element(t_data *scene, char *ptr)
{
	if (ft_strncmp(ptr, "A", 1) == 0)
	{
		if (scene->ambient_set)
			return (ft_putstr_fd("Error\n Duplicates in .rt\n", STDERR_FILENO),
				EXIT_FAILURE);
		return (parse_ambient(scene, ptr));
	}
	if (ft_strncmp(ptr, "C", 1) == 0)
	{
		if (scene->camera_set)
			return (ft_putstr_fd("Error\n Duplicates in .rt\n", STDERR_FILENO),
				EXIT_FAILURE);
		return (parse_camera(scene, ptr));
	}
	if (ft_strncmp(ptr, "L", 1) == 0)
	{
		if (scene->light_set)
			return (ft_putstr_fd("Error\n Duplicates in .rt\n", STDERR_FILENO),
				EXIT_FAILURE);
		return (parse_light(scene, ptr));
	}
	return (EXIT_SUCCESS);
}

int	handle_object_element(t_data *scene, char *ptr)
{
	if (ft_strncmp(ptr, "sp", 2) == 0)
		return (parse_sphere(scene, ptr));
	if (ft_strncmp(ptr, "pl", 2) == 0)
		return (parse_plane(scene, ptr));
	if (ft_strncmp(ptr, "cy", 2) == 0)
		return (parse_cylinder(scene, ptr));
	return (EXIT_SUCCESS);
}

int	parse_scene(t_data *scene, int fd)
{
	char	*line;
	char	*ptr;

	line = get_next_line(fd);
	while (line != NULL)
	{
		ptr = line;
		while (is_valid_separator(*ptr) || *ptr == '\n')
			ptr++;
		if (handle_global_element(scene, ptr) == EXIT_FAILURE
			|| handle_object_element(scene, ptr) == EXIT_FAILURE)
		{
			free(line);
			return (EXIT_FAILURE);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (!scene->ambient_set || !scene->camera_set || !scene->light_set)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
