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

void	save_hit_values(t_object_hit *object_hit, t_vec3d hit_point, int type, int color, int index)
{
	object_hit->hit_point = hit_point;
	object_hit->object_type = type;
	object_hit->object_color = color;
	object_hit->object_index = index;
}

// Function to find the closest intersection with any object (spheres and planes)
bool	find_closest_object(t_data *data, t_vec3d origin, t_vec3d direction, t_object_hit *closest_hit)
{
	int i ;
	t_vec3d hit_point;
	bool hit; // Flag to check if any intersection occurs
	float min_distance;
	float distance; //TODO maybe set up to 0 if it shows uninitialised value
	int color;

	i = 0;
	hit = false;
	min_distance = INFINITY; // Initially set the minimum distance to infinity
	while (i < data->sphere_count)
	{
		if (ray_sphere_intersection(data->spheres[i], origin, direction, &hit_point))
		{
			distance = calculate_distance(origin, hit_point);
			if (distance < min_distance)
			{
				min_distance = distance;
				color = convert_rgb_to_int(data->spheres[i].color);
				save_hit_values(closest_hit, hit_point, SPHERE, color, i);
				hit = true;
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
				color = convert_rgb_to_int(data->planes[i].color);
				save_hit_values(closest_hit, hit_point, PLANE, color, i);
                hit = true;
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
				color = convert_rgb_to_int(data->cylinders[i].color);
				save_hit_values(closest_hit, hit_point, CYLINDER, color, i);
				hit = true;
			}
		}
		// if (ray_cylinder_top(data->cylinders[i], origin, direction, &hit_point))
		// {
        //     distance = calculate_distance(origin, hit_point);
        //     if (distance < min_distance)
        //     {
        //         min_distance = distance;
		// 		color = convert_rgb_to_int(data->cylinders[i].color);
        //         save_hit_values(closest_hit, hit_point, CY_TOP, color, i);
        //         hit = true;
        //     }
        // }

        // if (ray_cylinder_bottom(data->cylinders[i], origin, direction, &hit_point))
        // {
        //     distance = calculate_distance(origin, hit_point);
        //     if (distance < min_distance)
        //     {
        //         min_distance = distance;
		// 		color = convert_rgb_to_int(data->cylinders[i].color);
        //         save_hit_values(closest_hit, hit_point, CY_BOTTOM, color, i);
        //         hit = true;
        //     }
        // }
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
// t_vec3d cylinder_normal(t_cylinder cylinder, t_vec3d hit_point)
// {
//     // Vector from cylinder center to hit point
//     t_vec3d center_to_hit = subtract_vector(hit_point, cylinder.center);
//     // Project the vector onto the cylinder axis to find the closest point on the axis
//     float projection_length = dot_product(center_to_hit, cylinder.axis);
    
//     // If the intersection point is on the bottom cap
//     if (projection_length <= 0) {
//         return normalize(scale_vector(cylinder.axis, -1)); // Normal points inward for bottom cap
//     }
//     // If the intersection point is on the top cap
//     else if (projection_length >= cylinder.height) {
//         return normalize(cylinder.axis); // Normal points outward for top cap
//     }

//     // Otherwise, calculate the normal for the cylindrical surface
//     t_vec3d closest_point_on_axis = add_vector(cylinder.center, scale_vector(cylinder.axis, projection_length));
//     t_vec3d normal = subtract_vector(hit_point, closest_point_on_axis);
//     return normalize(normal);
// }

t_vec3d cylinder_normal(t_cylinder cylinder, t_vec3d hit_point)
{
    // Vector from cylinder center to hit point
    t_vec3d center_to_hit = subtract_vector(hit_point, cylinder.center);
    // Project the vector onto the cylinder axis to find the closest point on the axis
    float projection_length = dot_product(center_to_hit, cylinder.axis);

    float epsilon = 1e-6; // Small value to prevent precision issues
    float bottom_cap_threshold = 0; // Assuming the bottom cap is at y = 0

    // Check if the intersection point is on the bottom circle
    if (projection_length < epsilon && hit_point.y <= bottom_cap_threshold + epsilon) {
        // Normal points outward for the bottom cap
        return normalize(scale_vector(cylinder.axis, -1));
    }

    // Return a zero vector if the hit point is not on the bottom circle
    return (t_vec3d){0, 0, 0}; // No normal for other areas
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
	float px = (2.0f * x / screen_width - 1.0f) * aspect_ratio * scale;
	float py = (1.0f - 2.0f * y / screen_height) * scale;

	direction.x = forward.x + px * right.x + py * up.x;
	direction.y = forward.y + px * right.y + py * up.y;
	direction.z = forward.z + px * right.z + py * up.z;

	direction = normalize(direction);

    // Find the closest intersection among all objects (spheres and planes)
	t_object_hit closest_hit;
	int color_code;
	if (find_closest_object(data, origin, direction, &closest_hit))
	{
		t_vec3d normal;

		if (closest_hit.object_type == SPHERE)
			normal = sphere_normal(data->spheres[closest_hit.object_index], closest_hit.hit_point);
		else if (closest_hit.object_type == PLANE)
			normal = data->planes[closest_hit.object_index].normal;
		else if (closest_hit.object_type == CYLINDER)
			normal = cylinder_normal(data->cylinders[closest_hit.object_index], closest_hit.hit_point);
		t_vec3d light_dir = normalize(subtract_vector(data->light.position, closest_hit.hit_point));

		// calculating light intensity. are we allowed to use fmax()?
		float ambient_intensity = data->ambient.ratio;
		float diffuse_intensity = fmax(0.0f, dot_product(normal, light_dir)) * data->light.brightness;

		// Combine ambient and diffuse components for the final intensity
		float light_intensity = ambient_intensity + diffuse_intensity;

		// Clamp the final intensity to [0, 1] to avoid over-brightening
		light_intensity = fmin(light_intensity, 1.0f);

		// adding darkening to base light
		int base_color = closest_hit.object_color;
		color_code = apply_shading(base_color, light_intensity);
		my_mlx_pixel_put(data->img, x, y, color_code);
	}
	else
	{
		// TODO: put it in separate function. Question: in above function do we need to take ambient in consideration as well?
		color_code = ((int)(data->ambient.color.red * data->ambient.ratio) << 16) | ((int)(data->ambient.color.green * data->ambient.ratio) << 8) | (int)(data->ambient.color.blue  * data->ambient.ratio);
		my_mlx_pixel_put(data->img, x, y, color_code);
	}
}
