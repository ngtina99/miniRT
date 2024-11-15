/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 20:23:35 by yioffe            #+#    #+#             */
/*   Updated: 2024/11/15 23:16:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_vec3d	cylinder_normal(t_cylinder cylinder, t_vec3d hit_point)
{
    t_vec3d axis = normalize(cylinder.axis);
    // Calculate base and top centers based on the cylinder's center and height
    t_vec3d base_center = subtract_vector(cylinder.center, scale_vector(axis, cylinder.height / 2.0f));
    t_vec3d top_center = add_vector(cylinder.center, scale_vector(axis, cylinder.height / 2.0f));
 	t_vec3d	oc;
    float	projection;
    t_vec3d	closest_point;
    t_vec3d	normal;
    // Check if the hit point is on the top cap
    if (fabs(dot_product(subtract_vector(hit_point, top_center), axis)) < EPSILON)
		return (axis); 
    // Check if the hit point is on the bottom cap
    else if (fabs(dot_product(subtract_vector(hit_point, base_center), axis)) < EPSILON)
        return (scale_vector(axis, -1.0f));
    else
    {
        // Calculate normal for the side surface
		oc = subtract_vector(hit_point, cylinder.center);
		projection = dot_product(oc, axis);
		closest_point = add_vector(cylinder.center, scale_vector(axis, projection));
		normal = subtract_vector(hit_point, closest_point);
        return normalize(normal);
    }
}

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
    /* Check if the intersection is within the cylinder's height */
	return (height_projection >= -cylinder.height / 2.0f && height_projection <= cylinder.height / 2.0f);
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
