/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:49:52 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/10/15 15:21:14 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// TODO: check uniqueness of capital letter params
// TODO: check whitespaces handling
// TODO: check invalid cases (now we return EXIT_SUCCESS a lot with no other cases). add validations that all params are present

// Function to add any form (cylinder, plane, sphere) to the array
int add_form(void **array, int *count, int *capacity, void *new_form, size_t form_size) {
    // Check if we need to initialize or expand the array
    if (*count == 0) {
        *capacity = INITIAL_CAPACITY;
        *array = malloc(form_size * (*capacity));
        if (!*array) {
            printf("Error: Memory allocation failed for array.\n");
            return(EXIT_FAILURE);
        }
    } else if (*count == *capacity) {
        void *new_array = malloc(form_size * (*capacity) * 2);
        if (!new_array) {
            printf("Error: Memory allocation failed when expanding array.\n");
            return(EXIT_FAILURE);
        }
        
        int i = 0;
        while (i < *count) {
            ft_memcpy((char*)new_array + i * form_size, (char*)(*array) + i * form_size, form_size);
            i++;
        }
        
        free(*array);
        *array = new_array;
        *capacity *= 2;
    }

    // Copy the new form into the array
    ft_memcpy((char*)(*array) + (*count) * form_size, new_form, form_size);
    (*count)++;
	return (EXIT_SUCCESS);
}

void initialize_scene(t_data *scene) 
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

float parse_float(char **line) {
    float result = 0.0;
    float fraction = 1.0;
    int sign = 1;
    int is_fractional = 0;

    // Skip leading spaces
    while (**line == ' ') {
        (*line)++;
    }

    // Check for a sign
    if (**line == '-') {
        sign = -1;
        (*line)++;
    } else if (**line == '+') {
        (*line)++;
    }

    // Parse the integer and fractional parts
    while (ft_isdigit(**line) || **line == '.') {
        if (**line == '.') {
            is_fractional = 1;
            (*line)++;
            continue;
        }
        if (!is_fractional) {
            result = result * 10.0 + (**line - '0');  // Parse integer part
        } else {
            fraction *= 0.1;
            result += (**line - '0') * fraction;  // Parse fractional part
        }
        (*line)++;
    }

    // Skip any spaces after the number
    while (**line == ' ') {
        (*line)++;
    }

    return result * sign;
}

// Function to parse a vector (x, y, z) from a string
int parse_vector(char **line, float *vector) {
    vector[0] = parse_float(line);
    if (**line == ',') (*line)++;  // Skip comma
    vector[1] = parse_float(line);
    if (**line == ',') (*line)++;  // Skip comma
    vector[2] = parse_float(line);
	return EXIT_SUCCESS;
}

// Function to parse an RGB color (r, g, b) from a string
int parse_rgb(char **line, int *color) {
    color[0] = ft_atoi(*line);  // Parse first RGB value
    while (**line != ',' && **line != '\0') (*line)++;  // Move past digits
    if (**line == ',') (*line)++;  // Skip comma

    color[1] = ft_atoi(*line);  // Parse second RGB value
    while (**line != ',' && **line != '\0') (*line)++;  // Move past digits
    if (**line == ',') (*line)++;  // Skip comma

    color[2] = ft_atoi(*line);  // Parse third RGB value
    while (**line != ' ' && **line != '\0') (*line)++;  // Move past digits and any trailing spaces
	return EXIT_SUCCESS;
}


int parse_ambient(t_data *scene, char *line) {
    t_ambient ambient;
    line++;  // Skip identifier 'A'
    ambient.ratio = parse_float(&line);  // Parse ambient lighting ratio
    parse_rgb(&line, ambient.color);  // Parse RGB color
    scene->ambient = ambient;  // Store in the scene

	return EXIT_SUCCESS;
}

int parse_camera(t_data *scene, char *line) {
    t_camera camera;
    line++;  // Skip identifier 'C'
    parse_vector(&line, camera.position);  // Parse position (x, y, z)
    parse_vector(&line, camera.orientation);  // Parse orientation vector
    camera.fov = (int)parse_float(&line);  // Parse field of view (FOV)
    scene->camera = camera;  // Store in the scene
	return EXIT_SUCCESS;
}

int parse_light(t_data *scene, char *line) {
    t_light light;
    line++;  // Skip identifier 'L'
    parse_vector(&line, light.position);  // Parse light position (x, y, z)
    light.brightness = parse_float(&line);  // Parse brightness ratio
    parse_rgb(&line, light.color);  // Parse RGB color
    scene->light = light;  // Store in the scene
	return EXIT_SUCCESS;
}

int parse_sphere(t_data *scene, char *line) {
    t_sphere sphere;
	int		result;

    line += 2;  // Skip identifier 'sp'
    parse_vector(&line, sphere.center);  // Parse sphere center (x, y, z)
    sphere.diameter = parse_float(&line);  // Parse diameter
    parse_rgb(&line, sphere.color);  // Parse RGB color
    return add_form((void**)&scene->spheres, &scene->sphere_count, &scene->sphere_capacity, &sphere, sizeof(t_sphere));
}

int parse_plane(t_data *scene, char *line) 
{
    t_plane plane;
    line += 2;  // Skip identifier 'pl'
    parse_vector(&line, plane.point);  // Parse a point on the plane (x, y, z)
    parse_vector(&line, plane.normal);  // Parse normal vector
    parse_rgb(&line, plane.color);  // Parse RGB color
	return add_form((void**)&scene->planes, &scene->plane_count, &scene->plane_capacity, &plane, sizeof(t_plane));
}

int parse_cylinder(t_data *scene, char *line) 
{
    t_cylinder cylinder;
    line += 2;  // Skip identifier 'cy'
    parse_vector(&line, cylinder.center);  // Parse cylinder center (x, y, z)
    parse_vector(&line, cylinder.axis);  // Parse axis direction
    cylinder.diameter = parse_float(&line);  // Parse diameter
    cylinder.height = parse_float(&line);  // Parse height
    parse_rgb(&line, cylinder.color);  // Parse RGB color
    return add_form((void**)&scene->cylinders, &scene->cylinder_count, &scene->cylinder_capacity, &cylinder, sizeof(t_cylinder));
}

int parse_scene(t_data *scene, int fd) 
{
    char *line;

    while ((line = get_next_line(fd)) != NULL) {
        char *ptr = line;
		int	curr_result;
        
        // Skip spaces and newlines at the start
        while (*ptr == ' ' || *ptr == '\n') ptr++;  

        // Identify and process the line based on its identifier
		// TODO: verify uniqueness - if not unique, clean and exit
        if (ft_strncmp(ptr, "A", 1) == 0) 
		{
            curr_result = parse_ambient(scene, ptr);
        } 
		else if (ft_strncmp(ptr, "C", 1) == 0) {
            curr_result = parse_camera(scene, ptr);
        } else if (ft_strncmp(ptr, "L", 1) == 0) {
            curr_result = parse_light(scene, ptr);
        } else if (ft_strncmp(ptr, "sp", 2) == 0) {
            curr_result = parse_sphere(scene, ptr);
        } else if (ft_strncmp(ptr, "pl", 2) == 0) {
            curr_result = parse_plane(scene, ptr);
        } else if (ft_strncmp(ptr, "cy", 2) == 0) {
            curr_result = parse_cylinder(scene, ptr);
        }

        // Free the line after processing
        free(line);
		//if (curr_result == EXIT_FAILURE)
			// TODO: clean all and stop
		//	free_scene(scene);
		//	return (EXIT_FAILURE);
    }
	return (EXIT_SUCCESS);
}


