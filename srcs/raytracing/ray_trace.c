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

/*
This function will check if there is an object between the hit point and the light 
source.
Calls find_closest_object with the light_dir to check if any objects intersect the path to the light.
If an intersection is found, it checks if the hit point of this intersection is closer to the original hit 
point than the light source, indicating the point is in shadow.
*/
t_light_info	calculate_object_lighting(t_data *data, t_light_info light, t_vec3d normal, t_object_hit closest_hit)
{
	float	ambient_intensity;
	float	diffuse_intensity;
	t_vec3d	offset_hit_point;

	ambient_intensity = data->ambient.ratio;
	diffuse_intensity = fmax(0.0f, dot_product(normal, light.light_dir)) * data->light.brightness;
	offset_hit_point = add_vector(closest_hit.hit_point, scale_vector(normal, 0.001f));
	// Combine ambient and diffuse components for the final intensity
	//2 here we check if shadow should be applied or not
	// if it's in the shadow, only ambient should be applied
	if (is_in_shadow(data, offset_hit_point, light.light_dir))
		light.light_intensity = ambient_intensity; // In shadow, apply only ambient lighting
	else
		light.light_intensity = ambient_intensity + diffuse_intensity; // Not in shadow, apply both ambient and diffuse lighting
	// Clamp the final intensity to [0, 1] to avoid over-brightening
	light.light_intensity = fmin(light.light_intensity, 1.0f);
	return (light);
}

void	calculate_object_color(t_data *data, t_object_hit closest_hit, t_light_info light)
{
	// calculating light intensity. are we allowed to use fmax()?
	// adding darkening to base light
	//calculate_object_color(data, closest_hit, x, y);
	int	base_color;
	int	color_code;

	base_color = closest_hit.object_color;
	color_code = (apply_shading(base_color, light.light_intensity));
	set_pixel_color(data->img, light.x, light.y, color_code);
}

void	calculate_background_color(t_data *data, int x, int y)
{
	int	color_code;
	int	red_color;
	int	green_color;
	int	blue_color;

	red_color = ((int)(data->ambient.color.red * data->ambient.ratio) << 16);
	green_color = ((int)(data->ambient.color.green * data->ambient.ratio) << 8);
	blue_color = (int)(data->ambient.color.blue * data->ambient.ratio);
	color_code = red_color | green_color | blue_color;
	set_pixel_color(data->img, x, y, color_code);
}

void	ray_trace(t_data *data, int x, int y)
{
	t_vec3d			direction; // Ray direction
	t_object_hit	closest_hit;
	t_vec3d			normal;
	t_light_info	light;

	direction = setup_camera(data, x, y);
	if (find_closest_object(data, data->camera.position, direction, &closest_hit))
	{
		light.x = x;
		light.y = y;
		if (closest_hit.object_type == SPHERE)
			normal = sphere_normal(data->spheres[closest_hit.object_index], closest_hit.hit_point);
		else if (closest_hit.object_type == PLANE)
			normal = data->planes[closest_hit.object_index].normal;
		else if (closest_hit.object_type == CYLINDER)
			normal = cylinder_normal(data->cylinders[closest_hit.object_index], closest_hit.hit_point);
		light.light_dir = normalize(subtract_vector(data->light.position, closest_hit.hit_point));
		light = calculate_object_lighting(data, light, normal, closest_hit); // get the light_intensity
		calculate_object_color(data, closest_hit, light);
	}
	else
		calculate_background_color(data, x, y);
}
