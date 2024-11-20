/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 20:23:35 by yioffe            #+#    #+#             */
/*   Updated: 2024/11/20 19:59:19 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_vec3d	cylinder_normal(t_cylinder cylinder, t_vec3d hit_point)
{
	t_cy_norm	norm;
	t_vec3d		oc;
	float		projection;
	t_vec3d		closest_point;

	norm.axis = normalize(cylinder.axis);
	norm.base_center = subtract_vector(cylinder.center, scale_vector(norm.axis,
				cylinder.height / 2.0f));
	norm.top_center = add_vector(cylinder.center, scale_vector(norm.axis,
				cylinder.height / 2.0f));
	if (fabs(dot_product(subtract_vector(hit_point, norm.top_center),
				norm.axis)) < EPSILON)
		return (norm.axis);
	else if (fabs(dot_product(subtract_vector(hit_point, norm.base_center),
				norm.axis)) < EPSILON)
		return (scale_vector(norm.axis, -1.0f));
	else
	{
		oc = subtract_vector(hit_point, cylinder.center);
		projection = dot_product(oc, norm.axis);
		closest_point = add_vector(cylinder.center, scale_vector(norm.axis,
					projection));
		return (normalize(subtract_vector(hit_point, closest_point)));
	}
}

bool	calculate_quadratic_coefficients(t_discr_util *discr,
		t_cy_intersection_util *util, t_cylinder cyl)
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
	return (height_projection >= -cylinder.height / 2.0f
		&& height_projection <= cylinder.height / 2.0f);
}

bool	calculate_intersection_point(t_vec3d ray_origin, t_vec3d ray_direction,
		float t, t_vec3d *intersection)
{
	if (t < 0)
		return (false);
	*intersection = add_vector(ray_origin, scale_vector(ray_direction, t));
	return (true);
}

bool	incap_radius(t_vec3d point, t_vec3d cap_center, float cap_radius)
{
	t_vec3d	diff;
	float	distance_squared;

	diff = subtract_vector(point, cap_center);
	distance_squared = dot_product(diff, diff);
	return (distance_squared <= cap_radius * cap_radius);
}
