/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:28:19 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/11/19 16:13:46 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

float	calculate_nearest_inters_p(float a, float b, float discriminant)
{
	float	t;
	float	t1;
	float	t2;

	t1 = (-b - sqrtf(discriminant)) / (2.0f * a);
	t2 = (-b + sqrtf(discriminant)) / (2.0f * a);
	if (t1 > 0)
		t = t1;
	else
		t = t2;
	return (t);
}

bool	ray_plane_intersection(t_plane plane, t_vec3d ray_origin,
		t_vec3d ray_direction, t_vec3d *hit_point)
{
	float	parallel_factor;
	t_vec3d	plane_to_origin;
	float	intersection_distance;

	parallel_factor = dot_product(ray_direction, plane.normal);
	if (fabs(parallel_factor) > 1e-6)
	{
		plane_to_origin = subtract_vector(plane.point, ray_origin);
		intersection_distance = dot_product(plane_to_origin, plane.normal)
			/ parallel_factor;
		if (intersection_distance >= 0)
		{
			*hit_point = add_vector(ray_origin, (scale_vector(ray_direction,
							intersection_distance)));
			return (true);
		}
	}
	return (false);
}

t_vec3d	sphere_normal(t_sphere sphere, t_vec3d hit_point)
{
	t_vec3d	normal;

	normal = subtract_vector(hit_point, sphere.center);
	return (normalize(normal));
}

bool	ray_sphere_intersection(t_sphere sphere, t_vec3d ray_origin,
		t_vec3d ray_direction, t_vec3d *hit_point)
{
	t_discr_util	discr;
	float			t;
	float			radius;
	t_vec3d			oc;

	radius = sphere.diameter / 2.0f;
	oc = subtract_vector(ray_origin, sphere.center);
	discr.a = dot_product(ray_direction, ray_direction);
	discr.b = 2.0f * dot_product(oc, ray_direction);
	discr.c = dot_product(oc, oc) - radius * radius;
	discr.discriminant = discr.b * discr.b - 4 * discr.a * discr.c;
	if (discr.discriminant < 0)
		return (false);
	t = calculate_nearest_inters_p(discr.a, discr.b, discr.discriminant);
	if (t < 0)
		return (false);
	*hit_point = add_vector(ray_origin, (scale_vector(ray_direction, t)));
	return (true);
}
