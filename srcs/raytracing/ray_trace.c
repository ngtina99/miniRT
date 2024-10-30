/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_calculation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:28:19 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/10/17 17:28:19 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Function to find the closest intersection with any object (spheres and planes)
int	find_closest_object(t_data *data, t_vec3d origin, t_vec3d direction, t_vec3d *closest_hit_point, int *object_type, int *object_index)
{
	int i ;
	t_vec3d hit_point;
	int hit; // Flag to check if any intersection occurs
	float min_distance;
	float distance; //TODO maybe set up to 0 if it shows uninitialised value

	i = 0;
	hit = 0;
	min_distance = INFINITY; // Initially set the minimum distance to infinity
	while (i < data->sphere_count)
	{
		if (ray_sphere_intersection(data->spheres[i], origin, direction, &hit_point))
		{
			distance = calculate_distance(origin, hit_point);
			if (distance < min_distance)
			{
				min_distance = distance;
				*closest_hit_point = hit_point;
				*object_type = SPHERE;
				*object_index = i;
				hit = 1;
			}
		}
		i++;
	}
	i = 0;
	while (i < data->plane_count)
	{
		if (ray_plane_intersection(data->planes[i], origin, direction, &hit_point))
		{
            distance = calculate_distance(origin, hit_point);
            if (distance < min_distance)
            {
                min_distance = distance;
                *closest_hit_point = hit_point;
                *object_type = PLANE;
                *object_index = i;
                hit = 1;
            }
        }
        i++;
    }
    i = 0;
    while (i < data->cylinder_count)
    {
		if (ray_cylinder_intersection(data->cylinders[i], origin, direction, &hit_point))
		{
			distance = calculate_distance(origin, hit_point);
			if (distance < min_distance)
			{
				min_distance = distance;
				*closest_hit_point = hit_point;
				*object_type = CYLINDER;
				*object_index = i;
				hit = 1;
				}
		}
		if (ray_cylinder_top(data->cylinders[i], origin, direction, &hit_point))
		{
            distance = calculate_distance(origin, hit_point);
            if (distance < min_distance)
            {
                min_distance = distance;
                *closest_hit_point = hit_point;
                *object_type = CY_TOP;
                *object_index = i;
                hit = 1;
            }
        }

        if (ray_cylinder_bottom(data->cylinders[i], origin, direction, &hit_point))
        {
            distance = calculate_distance(origin, hit_point);
            if (distance < min_distance)
            {
                min_distance = distance;
                *closest_hit_point = hit_point;
                *object_type = CY_BOTTOM;
                *object_index = i;
                hit = 1;
            }
        }
        i++;
    }
    return (hit); // Return whether any intersection was found
}

int apply_shading(int base_color, float intensity) 
{
    int red = ((base_color >> 16) & 0xFF) * intensity;
    int green = ((base_color >> 8) & 0xFF) * intensity;
    int blue = (base_color & 0xFF) * intensity;
    return (red << 16) | (green << 8) | blue;
}

t_vec3d sphere_normal(t_sphere sphere, t_vec3d hit_point)
{
    t_vec3d normal = subtract_vector(hit_point, sphere.center); // vector from the center to intersection
    return normalize(normal); // vector normalization
}

//not good yet!
t_vec3d cylinder_normal(t_cylinder cylinder, t_vec3d hit_point)
{
    t_vec3d center_to_hit = subtract_vector(hit_point, cylinder.center);
    float projection_length = dot_product(center_to_hit, cylinder.axis);

    t_vec3d closest_point_on_axis = add_vector(cylinder.center, scale_vector(cylinder.axis, projection_length));

    t_vec3d normal = subtract_vector(hit_point, closest_point_on_axis);
    return normalize(normal);
}



void	ray_trace(t_data *data, int x, int y, int screen_width, int screen_height)
{
	t_vec3d origin;    // Camera position
	t_vec3d direction; // Ray direction

	// Camera forward vector and its normalization
	t_vec3d forward;
	forward = normalize(data->camera.orientation);

    // Calculate the right and up vectors for the camera's orientation
	t_vec3d world_up = {0.0f, 1.0f, 0.0f};
	t_vec3d right = normalize(cross_product(forward, world_up));
	t_vec3d up = normalize(cross_product(right, forward));

    // Field of view and aspect ratio scaling
	float aspect_ratio = (float)screen_width / screen_height;
	float scale = tan(data->camera.fov * 0.5 * M_PI / 180.0f);

    // Camera position as ray origin
	origin = data->camera.position;

    // Calculate the ray direction for each pixel
	float px = (2.0f * x / screen_width - 1.0f) * scale;
	float py = (1.0f - 2.0f * y / screen_height) * scale / aspect_ratio;

	direction.x = forward.x + px * right.x + py * up.x;
	direction.y = forward.y + px * right.y + py * up.y;
	direction.z = forward.z + px * right.z + py * up.z;

	direction = normalize(direction);

    // Find the closest intersection among all objects (spheres and planes)
	t_vec3d closest_hit_point; // TODO is it needed later?
	int object_type;
	int object_index;
	int color_code;
	int ambient_color;
	if (find_closest_object(data, origin, direction, &closest_hit_point, &object_type, &object_index))
	{
		t_vec3d normal;

		if (object_type == SPHERE)
			normal = sphere_normal(data->spheres[object_index], closest_hit_point);
		else if (object_type == PLANE)
			normal = data->planes[object_index].normal;
		else if (object_type == CYLINDER)
			normal = cylinder_normal(data->cylinders[object_index], closest_hit_point);
		t_vec3d light_dir = normalize(subtract_vector(data->light.position, closest_hit_point));

		// calculating light intensity. can we use fmax()?
		float light_intensity = fmax(0.0, dot_product(normal, light_dir)) * data->light.brightness;

		// adding darkening to base light
		int base_color;
		if (object_type == SPHERE)
			base_color = convert_rgb_to_int(data->spheres[object_index].color);
		else if (object_type == PLANE)
			base_color = convert_rgb_to_int(data->planes[object_index].color);
		else
			base_color = convert_rgb_to_int(data->cylinders[object_index].color);

		color_code = apply_shading(base_color, light_intensity);
		my_mlx_pixel_put(data->img, x, y, color_code);
	}
	else
	{
		ambient_color = (int)(255 * data->ambient.ratio);
		color_code = (ambient_color << 16) | (ambient_color << 8) | ambient_color;
		my_mlx_pixel_put(data->img, x, y, color_code);
	}
}
