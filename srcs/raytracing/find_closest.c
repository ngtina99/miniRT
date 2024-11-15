/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngtina1999 <ngtina1999@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:28:19 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/11/09 02:14:23 by ngtina1999       ###   ########.fr       */
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
	int		i;
	t_vec3d	hit_point;
	bool	hit; // Flag to check if any intersection occurs
	float	min_distance;
	float	distance; //TODO maybe set up to 0 if it shows uninitialised value
	int		color;

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
		if (ray_cylinder_top(data->cylinders[i], origin, direction, &hit_point))
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
		if (ray_cylinder_bottom(data->cylinders[i], origin, direction, &hit_point))
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
		i++;
    }
    return (hit); // Return whether any intersection was found
}