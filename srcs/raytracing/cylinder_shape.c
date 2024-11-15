/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_shape.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 01:32:47 by ngtina1999        #+#    #+#             */
/*   Updated: 2024/11/15 23:27:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	ray_cylinder_intersection(t_cylinder cylinder, t_vec3d ray_origin,
		t_vec3d ray_direction, t_vec3d *hit_point)
{
	t_vec3d					oc;
	t_discr_util			discr;
	t_cy_intersection_util	util;
	float					t;

	oc = subtract_vector(ray_origin, cylinder.center);
	util.cylinder_axis = normalize(cylinder.axis);
	/* Decompose ray direction and oc into parallel
	and perpendicular components */
	util.ray_dir_parallel = dot_product(ray_direction, util.cylinder_axis);
	util.ray_dir_perp = subtract_vector(ray_direction,
			scale_vector(util.cylinder_axis, util.ray_dir_parallel));
	util.oc_parallel = dot_product(oc, util.cylinder_axis);
	util.oc_perp = subtract_vector(oc, scale_vector(util.cylinder_axis,
				util.oc_parallel));
	/* Calculate quadratic coefficients and check discriminant */
	if (!calculate_quadratic_coefficients(&discr, &util, oc, cylinder))
		return (false);
	/* Calculate nearest intersection point */
	t = calculate_nearest_inters_p(discr.a, discr.b, discr.discriminant);
	if (t < 0)
		return (false);
	/* Calculate intersection and check within cylinder height */
	*hit_point = add_vector(ray_origin, scale_vector(ray_direction, t));
	return (check_cylinder_height(*hit_point, cylinder, util.cylinder_axis));
}

bool	ray_cylinder_top(t_cylinder cylinder, t_vec3d ray_origin,
						t_vec3d ray_direction, t_vec3d *hit_point)
{
	t_vec3d	top_center;
	float	parallel_factor;
	float	t;
	t_vec3d	cyl_axis;

	cyl_axis = normalize(cylinder.axis);
    /* Calculate top center */
	top_center = add_vector(cylinder.center, scale_vector(cyl_axis, cylinder.height / 2.0f));
	parallel_factor = dot_product(ray_direction, cyl_axis);
	if (fabs(parallel_factor) < 1e-6)
		return (false);
    /* Calculate t for intersection with top cap */
	t = dot_product(subtract_vector(top_center, ray_origin), cyl_axis) / parallel_factor;
	if (!calculate_intersection_point(ray_origin, ray_direction, t, hit_point))
		return (false);
    /* Check if intersection point is within the cap radius */
	return (incap_radius(*hit_point, top_center, cylinder.diameter / 2.0f));
}

bool	ray_cylinder_bottom(t_cylinder cylinder, t_vec3d ray_origin,
					t_vec3d ray_direction, t_vec3d *hit_point)
{
	t_vec3d	bottom_center;
	float	parallel_factor;
	float	t;
	t_vec3d	cyl_axis;

	cyl_axis = normalize(cylinder.axis);
    /* Calculate bottom center */
	bottom_center = subtract_vector(cylinder.center, scale_vector(cyl_axis, cylinder.height / 2.0f));
	parallel_factor = dot_product(ray_direction, cyl_axis);
	if (fabs(parallel_factor) < 1e-6)
		return (false);
    /* Calculate t for intersection with bottom cap */
	t = dot_product(subtract_vector(bottom_center, ray_origin), cyl_axis) / parallel_factor;
	if (!calculate_intersection_point(ray_origin, ray_direction, t, hit_point))
		return (false);
    /* Check if intersection point is within the cap radius */
	return (incap_radius(*hit_point, bottom_center, cylinder.diameter / 2.0f));
}
