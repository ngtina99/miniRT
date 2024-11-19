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

void	save_hit_values(t_object_hit *object_hit, t_vec3d hit_point, t_obj_info obj, int index)
{
	object_hit->hit_point = hit_point;
	object_hit->object_type = obj.type;
	object_hit->object_color = obj.color;
	object_hit->object_index = index;
}

bool	find_closest_object(t_data *data, t_vec3d origin, t_vec3d direction, t_object_hit *closest_hit)
{
	int				i;
	t_vec3d			hit_point;
	t_inter_info	inter;
	t_obj_info		obj;

	i = 0;
	inter.hit = false;
	inter.min_distance = INFINITY;
	while (i < data->sphere_count)
	{
		if (ray_sphere_intersection(data->spheres[i], origin, direction, &hit_point))
		{
			inter.distance = calculate_distance(origin, hit_point);
			if (inter.distance < inter.min_distance)
			{
				inter.min_distance = inter.distance;
				obj.color = convert_rgb_to_int(data->spheres[i].color);
				obj.type = SPHERE;
				inter.hit = true;
				save_hit_values(closest_hit, hit_point, obj, i);
			}
		}
		i++;
	}
	i = 0;
	while (i < data->plane_count)
	{
		if (ray_plane_intersection(data->planes[i], origin, direction, &hit_point))
		{
			inter.distance = calculate_distance(origin, hit_point);
			if (inter.distance < inter.min_distance)
			{
				inter.min_distance = inter.distance;
				obj.color = convert_rgb_to_int(data->planes[i].color);
				obj.type = PLANE;
				inter.hit = true;
				save_hit_values(closest_hit, hit_point, obj, i);
			}
		}
		i++;
	}
	i = 0;
	while (i < data->cylinder_count)
	{
		if (ray_cylinder_intersection(data->cylinders[i], origin, direction, &hit_point))
		{
			inter.distance = calculate_distance(origin, hit_point);
			if (inter.distance < inter.min_distance)
			{
				inter.min_distance = inter.distance;
				obj.color = convert_rgb_to_int(data->cylinders[i].color);
				obj.type = CYLINDER;
				inter.hit = true;
				save_hit_values(closest_hit, hit_point, obj, i);
			}
		}
		if (ray_cylinder_top(data->cylinders[i], origin, direction, &hit_point))
		{
			inter.distance = calculate_distance(origin, hit_point);
			if (inter.distance < inter.min_distance)
			{
				inter.min_distance = inter.distance;
				obj.color = convert_rgb_to_int(data->cylinders[i].color);
				obj.type = CYLINDER;
				inter.hit = true;
				save_hit_values(closest_hit, hit_point, obj, i);
			}
		}
		if (ray_cylinder_bottom(data->cylinders[i], origin, direction, &hit_point))
		{
			inter.distance = calculate_distance(origin, hit_point);
			if (inter.distance < inter.min_distance)
			{
				inter.min_distance = inter.distance;
				obj.color = convert_rgb_to_int(data->cylinders[i].color);
				obj.type = CYLINDER;
				inter.hit = true;
				save_hit_values(closest_hit, hit_point, obj, i);
			}
		}
		i++;
	}
	return (inter.hit);
}
