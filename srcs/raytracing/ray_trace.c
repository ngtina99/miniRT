/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_calculation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: thuy-ngu <thuy-ngu@student.42lisboa.com    +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/10/17 17:28:19 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/10/17 17:28:19 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_light_info	calculate_object_lighting(t_data *data, t_light_info light,
		t_vec3d normal, t_object_hit closest_hit)
{
	float	ambient_intensity;
	float	diffuse_intensity;
	t_vec3d	offset_hit_point;

	ambient_intensity = data->ambient.ratio;
	diffuse_intensity = fmax(0.0f, dot_product(normal, light.light_dir))
		* data->light.brightness;
	offset_hit_point = add_vector(closest_hit.hit_point, scale_vector(normal,
				0.001f));
	if (is_in_shadow(data, offset_hit_point, light.light_dir))
		light.light_intensity = ambient_intensity;
	else
		light.light_intensity = ambient_intensity + diffuse_intensity;
	light.light_intensity = fmin(light.light_intensity, 1.0f);
	return (light);
}

void	calculate_object_color(t_data *data, t_object_hit closest_hit,
		t_light_info light)
{
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
	green_color = ((int)(data->ambient.color.green
				* data->ambient.ratio) << 8);
	blue_color = (int)(data->ambient.color.blue * data->ambient.ratio);
	color_code = red_color | green_color | blue_color;
	set_pixel_color(data->img, x, y, color_code);
}

static t_vec3d	get_object_normal(t_data *data, t_object_hit *closest_hit)
{
	if (closest_hit->object_type == SPHERE)
		return (sphere_normal(data->spheres[closest_hit->object_index],
				closest_hit->hit_point));
	else if (closest_hit->object_type == PLANE)
		return (data->planes[closest_hit->object_index].normal);
	else if (closest_hit->object_type == CYLINDER)
		return (cylinder_normal(data->cylinders[closest_hit->object_index],
				closest_hit->hit_point));
	return ((t_vec3d){0, 0, 0});
}

/* In this function we consider camera position as origin for each ray. */
void	ray_trace(t_data *data, int x, int y)
{
	t_vec3d			origin;
	t_vec3d			direction;
	t_object_hit	closest_hit;
	t_vec3d			normal;
	t_light_info	light;

	origin = data->camera.position;
	direction = setup_camera(data, x, y);
	if (find_closest_object(data, origin, direction, &closest_hit))
	{
		light.x = x;
		light.y = y;
		normal = get_object_normal(data, &closest_hit);
		light.light_dir = normalize(subtract_vector(data->light.position,
					closest_hit.hit_point));
		light = calculate_object_lighting(data, light, normal, closest_hit);
		calculate_object_color(data, closest_hit, light);
	}
	else
		calculate_background_color(data, x, y);
}
