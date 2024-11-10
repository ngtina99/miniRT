/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_shape.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 01:32:47 by ngtina1999        #+#    #+#             */
/*   Updated: 2024/11/10 20:15:54 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	calculate_quadratic_coefficients(t_discr_util *discr,
		t_cyl_intersection_util *util, t_vec3d oc, t_cylinder cyl)
{
	discr->a = dot_product(util->ray_dir_perp, util->ray_dir_perp);
	discr->b = 2.0f * dot_product(util->oc_perp, util->ray_dir_perp);
	discr->c = dot_product(util->oc_perp, util->oc_perp) - (cyl.diameter / 2.0f)
		* (cyl.diameter / 2.0f);
	discr->discriminant = discr->b * discr->b - 4 * discr->a * discr->c;
	return (discr->discriminant >= 0);
}

bool	check_cylinder_height(t_vec3d intersection, t_cylinder cylinder,
		t_vec3d cylinder_axis)
{
	t_vec3d	diff;
	float	height_projection;

	diff = subtract_vector(intersection, cylinder.center);
	height_projection = dot_product(diff, cylinder_axis);
	return (height_projection >= 0 && height_projection <= cylinder.height);
}

bool	ray_cylinder_intersection(t_cylinder cylinder, t_vec3d ray_origin,
		t_vec3d ray_direction, t_vec3d *hit_point)
{
	t_vec3d					oc;
	t_discr_util			discr;
	t_cyl_intersection_util	util;
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

bool	calculate_intersection_point(t_vec3d ray_origin, t_vec3d ray_direction,
		float t, t_vec3d *intersection)
{
	if (t < 0)
		return (false);
	*intersection = add_vector(ray_origin, scale_vector(ray_direction, t));
	return (true);
}

bool	within_cap_radius(t_vec3d point, t_vec3d cap_center, float cap_radius)
{
	t_vec3d	diff;
	float	distance_squared;

	diff = subtract_vector(point, cap_center);
	distance_squared = dot_product(diff, diff);
	return (distance_squared <= cap_radius * cap_radius);
}

bool	ray_cylinder_top(t_cylinder cylinder, t_vec3d ray_origin,
		t_vec3d ray_direction, t_vec3d *hit_point)
{
	t_vec3d	top_center;
	float	parallel_factor;
	float	t;

	/* Calculate top center and check parallel factor */
	top_center = add_vector(cylinder.center, scale_vector(cylinder.axis, cylinder.height / 2.0f));
	parallel_factor = dot_product(ray_direction, cylinder.axis);
	if (fabs(parallel_factor) < 1e-6)
		return (false);

	/* Calculate t for intersection with top cap */
	t = dot_product(subtract_vector(top_center, ray_origin), cylinder.axis) / parallel_factor;
	if (!calculate_intersection_point(ray_origin, ray_direction, t, hit_point))
		return (false);

	/* Check if intersection point is within the cap radius */
	return (within_cap_radius(*hit_point, top_center, cylinder.diameter / 2.0f));
}


bool	ray_cylinder_bottom(t_cylinder cylinder, t_vec3d ray_origin,
		t_vec3d ray_direction, t_vec3d *hit_point)
{
	t_vec3d	bottom_center;
	float	parallel_factor;
	t_vec3d	bottom_to_origin;
	float	t;
	t_vec3d	intersection_pt;
	t_vec3d	point_to_bottom;

	/* //subtract the half of the center to get the bottom center */
	bottom_center = subtract_vector(cylinder.center, scale_vector(cylinder.axis,
				0.0001f));
	/* // Calculate intersection with bottom plane */
	parallel_factor = dot_product(ray_direction, cylinder.axis);
	/* Ray is parallel to the bottom cap plane */
	if (fabs(parallel_factor) < 1e-6)
		return (false);
	/*  check if the ray hits the bottom */
	bottom_to_origin = subtract_vector(bottom_center, ray_origin);
	t = dot_product(bottom_to_origin, cylinder.axis) / parallel_factor;
	/* Cap intersection is behind the ray */
	if (t < 0)
		return (false);
	/* // Calculate exact intersection point */
	intersection_pt = add_vector(ray_origin, scale_vector(ray_direction, t));
	/* // Check if intersection point is within the cap radius */
	point_to_bottom = subtract_vector(intersection_pt, bottom_center);
	/* // Calculating the dot product of a vector with itself, dot_product(pb,
		pb),
	//  gives the squared length of that vector.
	// This squared distance is a shorthand for avoiding the costly square root operation
	// (from sqrt()), making it more efficient. */
	if ((dot_product(point_to_bottom, point_to_bottom)) <= (cylinder.diameter
			/ 2.0f) * (cylinder.diameter / 2.0f))
	{
		*hit_point = intersection_pt;
		return (true);
	}
	return (false);
}
