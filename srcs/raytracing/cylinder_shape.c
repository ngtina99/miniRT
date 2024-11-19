/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_shape.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 01:32:47 by ngtina1999        #+#    #+#             */
/*   Updated: 2024/11/19 17:08:20 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	ray_cylinder_intersection(t_cylinder cylinder, t_vec3d ray_origin,
		t_vec3d ray_direction, t_vec3d *hit_point)
{
	t_vec3d					origin_to_cylinder;
	t_discr_util			discr;
	t_cy_intersection_util	util;
	float					intersect_distance;

	origin_to_cylinder = subtract_vector(ray_origin, cylinder.center);
	util.cylinder_axis = normalize(cylinder.axis);
	util.ray_dir_parallel = dot_product(ray_direction, util.cylinder_axis);
	util.ray_dir_perp = subtract_vector(ray_direction,
			scale_vector(util.cylinder_axis, util.ray_dir_parallel));
	util.oc_parallel = dot_product(origin_to_cylinder, util.cylinder_axis);
	util.oc_perp = subtract_vector(origin_to_cylinder,
			scale_vector(util.cylinder_axis, util.oc_parallel));
	if (!calculate_quadratic_coefficients(&discr, &util,
			origin_to_cylinder, cylinder))
		return (false);
	intersect_distance = calculate_nearest_inters_p(discr.a, discr.b,
			discr.discriminant);
	if (intersect_distance < 0)
		return (false);
	*hit_point = add_vector(ray_origin,
			scale_vector(ray_direction, intersect_distance));
	return (check_cylinder_height(*hit_point, cylinder, util.cylinder_axis));
}

bool	ray_cylinder_top(t_cylinder cylinder, t_vec3d ray_origin,
						t_vec3d ray_direction, t_vec3d *hit_point)
{
	t_vec3d	top_center;
	float	parallel_factor;
	float	intersect_distance;
	t_vec3d	cyl_axis;

	cyl_axis = normalize(cylinder.axis);
	top_center = add_vector(cylinder.center,
			scale_vector(cyl_axis, cylinder.height / 2.0f));
	parallel_factor = dot_product(ray_direction, cyl_axis);
	if (fabs(parallel_factor) < 1e-6)
		return (false);
	intersect_distance = dot_product(subtract_vector(top_center,
				ray_origin), cyl_axis) / parallel_factor;
	if (!calculate_intersection_point(ray_origin, ray_direction,
			intersect_distance, hit_point))
		return (false);
	return (incap_radius(*hit_point, top_center, cylinder.diameter / 2.0f));
}

bool	ray_cylinder_bottom(t_cylinder cylinder, t_vec3d ray_origin,
					t_vec3d ray_direction, t_vec3d *hit_point)
{
	t_vec3d	bottom_center;
	float	parallel_factor;
	float	intersect_distance;
	t_vec3d	cyl_axis;

	cyl_axis = normalize(cylinder.axis);
	bottom_center = subtract_vector(cylinder.center,
			scale_vector(cyl_axis, cylinder.height / 2.0f));
	parallel_factor = dot_product(ray_direction, cyl_axis);
	if (fabs(parallel_factor) < 1e-6)
		return (false);
	intersect_distance = dot_product(subtract_vector(bottom_center, ray_origin),
			cyl_axis) / parallel_factor;
	if (!calculate_intersection_point(ray_origin, ray_direction,
			intersect_distance, hit_point))
		return (false);
	return (incap_radius(*hit_point, bottom_center, cylinder.diameter / 2.0f));
}

bool	ray_paraboloid_intersection(t_paraboloid paraboloid, t_vec3d ray_origin,
		t_vec3d ray_direction, t_vec3d *hit_point)
{
	t_vec3d		v_to_ray;
	t_discr_util	discr;
	float		intersection_distance;
	float		dot_axis_dir;
	float		dot_axis_vtr;

	paraboloid.axis = normalize(paraboloid.axis);
	v_to_ray = subtract_vector(ray_origin, paraboloid.vertex);
	dot_axis_dir = dot_product(ray_direction, paraboloid.axis);
	dot_axis_vtr = dot_product(v_to_ray, paraboloid.axis);
	discr.a = dot_product(ray_direction, ray_direction) - dot_axis_dir * dot_axis_dir
			- paraboloid.curvature * dot_axis_dir * dot_axis_dir;
	discr.b = 2.0f * (dot_product(ray_direction, v_to_ray)
			- dot_axis_dir * dot_axis_vtr
			- paraboloid.curvature * dot_axis_dir * dot_axis_vtr);
	discr.c = dot_product(v_to_ray, v_to_ray) - dot_axis_vtr * dot_axis_vtr
			- paraboloid.curvature * dot_axis_vtr * dot_axis_vtr;
	discr.discriminant = discr.b * discr.b - 4.0f * discr.a * discr.c;
	if (discr.discriminant < 0)
		return (false);
	intersection_distance = calculate_nearest_inters_p(discr.a, discr.b, discr.discriminant);
	if (intersection_distance < 0)
		return (false);
	*hit_point = add_vector(ray_origin, scale_vector(ray_direction, intersection_distance));
	return (check_paraboloid_height(*hit_point, paraboloid));
}

bool	check_paraboloid_height(t_vec3d intersection, t_paraboloid paraboloid)
{
	t_vec3d	v_to_hit;
	float	height_projection;

	v_to_hit = subtract_vector(intersection, paraboloid.vertex);
	height_projection = dot_product(v_to_hit, paraboloid.axis);
	return (height_projection >= 0 && height_projection <= paraboloid.height);
}

t_vec3d	paraboloid_normal(t_paraboloid paraboloid, t_vec3d hit_point)
{
	t_vec3d	v_to_hit;
	float	distance_to_axis;
	t_vec3d	axis_scaled;
	t_vec3d	projected_point;

	v_to_hit = subtract_vector(hit_point, paraboloid.vertex);
	distance_to_axis = dot_product(v_to_hit, paraboloid.axis);
	axis_scaled = scale_vector(paraboloid.axis, distance_to_axis);
	projected_point = add_vector(paraboloid.vertex, axis_scaled);
	return (normalize(subtract_vector(hit_point, projected_point)));
}
