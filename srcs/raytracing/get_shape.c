/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:28:19 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/11/17 10:28:26 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Calculate the nearest intersection point (t)
float	calculate_nearest_inters_p(float a, float b, float discriminant)
{
	float	t;
	float	t1;
	float	t2;

	t1 = (-b - sqrtf(discriminant)) / (2.0f * a);
	t2 = (-b + sqrtf(discriminant)) / (2.0f * a);
	// Choose the nearest t that's in front of the camera (positive t)
	// t = (t1 > 0) ? t1 : t2;
		// it was with this before norminette said it is banned
	if (t1 > 0)
		t = t1;
	else
		t = t2;
	return (t);
}

/*
	// Function to check if a ray intersects a plane and return the intersection point
// No Quadratic Equation: Unlike the sphere and cylinder cases,
	which lead to quadratic equations
// with potential multiple intersection points (hence the need for a discriminant),
	the ray-plane intersection
// resolves directly into a linear equation. The result gives a single value for 𝑡,
// which tells us the distance along the ray to the intersection point.

// serves to determine if the ray is parallel to the plane.
// If parallel_factor is close to zero,
	it indicates that the ray is parallel and will never intersect with the plane,
// similar to checking if the discriminant is negative for spheres or cylinders. */
/* // If parallel_factor is 0,
	it means the ray is parallel to the plane. In this case,
	there won't be an intersection since the ray will never cross the plane.
// If parallel_factor is greater than 0,
	it indicates that the ray is moving towards the plane (if the normal points outward).
// If parallel_factor is less than 0,
	it indicates that the ray is moving away from the plane.
	// Dot product between ray direction and the plane normal */
bool	ray_plane_intersection(t_plane plane, t_vec3d ray_origin,
		t_vec3d ray_direction, t_vec3d *hit_point)
{
	float	parallel_factor;
	t_vec3d	po;
	float	t;

	// po is from plane to origin
	// TODO: let's rename it to be clear from the name with no comments
	// TODO: also consider renaming t variable
	// If denom is close to 0, the ray is parallel to the plane,
	//	so no intersection
	parallel_factor = dot_product(ray_direction, plane.normal);
	if (fabs(parallel_factor) > 1e-6)
	{
		// Calculate vector from ray origin to a point on the plane
		po = subtract_vector(plane.point, ray_origin);
		// Calculate the distance along the ray to the intersection point (t)
		t = dot_product(po, plane.normal) / parallel_factor;
		// If t is positive, the intersection point is in front of the camera
		if (t >= 0)
		{
			// Calculate the intersection point
			*hit_point = add_vector(ray_origin, (scale_vector(ray_direction,
							t)));
			return (true);
		}
	}
	return (false);
}

t_vec3d	sphere_normal(t_sphere sphere, t_vec3d hit_point)
{
	t_vec3d	normal;

	// vector from the center to intersection
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
	/* // If both t values are negative, the intersection is behind the camera
	//printf("Both t1 and t2 are negative, intersection behind camera\n"); */
	t = calculate_nearest_inters_p(discr.a, discr.b, discr.discriminant);
	if (t < 0)
		// intersection is behind the camere
		return (false);
	*hit_point = add_vector(ray_origin, (scale_vector(ray_direction, t)));
	return (true);
}
