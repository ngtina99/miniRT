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
*/
/* Function to add any form (cylinder, plane, sphere) to the array */
int	add_form(void **array, int *count, int *capacity, void *new_form,
		size_t form_size)
{
	int		i;
	void	*new_array;

	if (*count == 0)
	{
		*capacity = INITIAL_CAPACITY;
		*array = malloc(form_size * (*capacity));
		if (!*array)
			return (perror("Error allocating memory"), EXIT_FAILURE);
	}
	else if (*count == *capacity)
	{
		new_array = malloc(form_size * (*capacity) * 2);
		if (!new_array)
			return (perror("Error allocating memory"), EXIT_FAILURE);
		i = 0;
		while (i < *count)
		{
			ft_memcpy((char *)new_array + i * form_size, (char *)(*array) + i
				* form_size, form_size);
			i++;
		}
		free(*array);
		*array = new_array;
		*capacity *= 2;
	}
	ft_memcpy((char *)(*array) + (*count) * form_size, new_form, form_size);
	(*count)++;
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
}

static void	skip_whitespace(char **line)
{
	while (**line == ' ')
		(*line)++;
}

static void	skip_invalid_chars(char **line)
{
	while (**line && **line != ' ' && !ft_isdigit(**line) && **line != ','
		&& **line != '.')
		(*line)++;
}

static int	parse_sign(char **line)
{
	int	sign;

	sign = 1;
	if (**line == '-')
	{
		sign = -1;
		(*line)++;
	}
	else if (**line == '+')
		(*line)++;
	return (sign);
}

static void	parse_number(char **line, float *result, float *fraction,
		bool *is_fractional)
{
	while (ft_isdigit(**line) || **line == '.')
	{
		if (**line == '.')
		{
			*is_fractional = true;
			(*line)++;
			continue ;
		}
		if (!(*is_fractional))
			*result = *result * 10.0 + (**line - '0');
		else
		{
			*fraction *= 0.1;
			*result += (**line - '0') * (*fraction);
		}
		(*line)++;
	}
}

float	parse_float(char **line)
{
	float	result;
	float	fraction;
	int		sign;
	bool	is_fractional;

	result = 0.0;
	fraction = 1.0;
	is_fractional = false;
	skip_whitespace(line);
	sign = parse_sign(line);
	parse_number(line, &result, &fraction, &is_fractional);
	skip_invalid_chars(line);
	skip_whitespace(line);
	return (result * sign);
}

int	parse_vector(char **line, t_vec3d *vector)
{
	vector->x = parse_float(line);
	if (**line == ',')
		(*line)++;
	vector->y = parse_float(line);
	if (**line == ',')
		(*line)++;
	vector->z = parse_float(line);
	return (EXIT_SUCCESS);
}

int	parse_rgb(char **line, t__color_rgb *color)
{
	color->red = ft_atoi(*line);
	while (**line != ',' && **line != '\0')
		(*line)++;
	if (**line == ',')
		(*line)++;
	color->green = ft_atoi(*line);
	while (**line != ',' && **line != '\0')
		(*line)++;
	if (**line == ',')
		(*line)++;
	color->blue = ft_atoi(*line);
	while (**line != ' ' && **line != '\0')
		(*line)++;
	return (EXIT_SUCCESS);
}

int	parse_ambient(t_data *scene, char *line)
{
	t_ambient	ambient;

	line++;
	ambient.ratio = parse_float(&line);
	parse_rgb(&line, &ambient.color);
	scene->ambient = ambient;
	return (EXIT_SUCCESS);
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

int	parse_scene(t_data *scene, int fd)
{
	char	*line;
	char	*ptr;
	int		curr_result;

	line = get_next_line(fd);
	while (line != NULL)
	{
		ptr = line;
		while (*ptr == ' ' || *ptr == '\n')
			ptr++;
		// TODO: verify uniqueness
		if (ft_strncmp(ptr, "A", 1) == 0)
			curr_result = parse_ambient(scene, ptr);
		else if (ft_strncmp(ptr, "C", 1) == 0)
			curr_result = parse_camera(scene, ptr);
		else if (ft_strncmp(ptr, "L", 1) == 0)
			curr_result = parse_light(scene, ptr);
		else if (ft_strncmp(ptr, "sp", 2) == 0)
			curr_result = parse_sphere(scene, ptr);
		else if (ft_strncmp(ptr, "pl", 2) == 0)
			curr_result = parse_plane(scene, ptr);
		else if (ft_strncmp(ptr, "cy", 2) == 0)
			curr_result = parse_cylinder(scene, ptr);
		free(line);
		line = get_next_line(fd);
		// if (curr_result == EXIT_FAILURE)
		// TODO: clean all and stop
		//	free_scene(scene);
		//	return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
