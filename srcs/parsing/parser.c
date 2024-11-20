/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/11/16 13:22:45 by yioffe            #+#    #+#             */
/*   Updated: 2024/11/16 13:22:45 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/* // TODO: check uniqueness of capital letter params
// TODO: check whitespaces handling
// TODO: check invalid cases (now we return EXIT_SUCCESS a lot
with no other cases).
	add validations that all params are present
// TODO: think about the case when lines are duplicate.
Not sure if needs validation
// TODO: mandatory/not mandatory parameters
// TODO: change initial size variable and try with valgrind
*/
/* Function to add any form (cylinder, plane, sphere) to the array */

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

int	parse_scene(t_data *scene, int fd)
{
	char	*line;
	char	*ptr;
	int		curr_result;

	line = get_next_line(fd);
	while (line != NULL)
	{
		ptr = line;
		while (is_valid_separator(*ptr) || *ptr == '\n')
			ptr++;
		if (ft_strncmp(ptr, "A", 1) == 0)
		{
			if (scene->ambient_set)
				return (ft_putstr_fd("Error\n Duplicates in .rt\n", STDERR_FILENO), EXIT_FAILURE);
			curr_result = parse_ambient(scene, ptr);
		}
		else if (ft_strncmp(ptr, "C", 1) == 0)
		{
			if (scene->camera_set)
				return (ft_putstr_fd("Error\n Duplicates in .rt\n", STDERR_FILENO), EXIT_FAILURE);
			curr_result = parse_camera(scene, ptr);
		}
		else if (ft_strncmp(ptr, "L", 1) == 0)
		{
			if (scene->light_set)
				return (ft_putstr_fd("Error\n Duplicates in .rt\n", STDERR_FILENO), EXIT_FAILURE);
			curr_result = parse_light(scene, ptr);
		}
		else if (ft_strncmp(ptr, "sp", 2) == 0)
			curr_result = parse_sphere(scene, ptr);
		else if (ft_strncmp(ptr, "pl", 2) == 0)
			curr_result = parse_plane(scene, ptr);
		else if (ft_strncmp(ptr, "cy", 2) == 0)
			curr_result = parse_cylinder(scene, ptr);
		free(line);
		if (curr_result == EXIT_FAILURE)
			return (EXIT_FAILURE);
		line = get_next_line(fd);
	}
	if (!scene->ambient_set || !scene->camera_set || !scene->light_set)
		return (EXIT_FAILURE);
	// if (count.a != 1 || count.c != 1 || count.l != 1 )
	// 	return (EXIT_FAILURE); // it is the same as yours just it is check if there are more of A C or L
	return (EXIT_SUCCESS);
}
