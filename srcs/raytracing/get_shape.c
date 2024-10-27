/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngtina1999 <ngtina1999@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:28:19 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/10/27 20:55:01 by ngtina1999       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// bool	calculate_discriminant(float a, float b, float c)
// {
// 	float discriminant;

// 	discriminant = b * b - 4 * a * c;
// }

bool	ray_sphere_intersection(t_sphere sphere, t_vec3d ray_origin, t_vec3d ray_direction, t_vec3d *hit_point)
{
	float radius;
	t_vec3d oc; //ray_origin to center

	radius = sphere.diameter / 2.0f;
	oc = subtract_vector(ray_origin, sphere.center);

	float a = dot_product(ray_direction, ray_direction);
	float b = 2.0f * dot_product(oc, ray_direction);
	float c = dot_product(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
		return (false); // No intersection
    else
    {
        // Calculate the nearest intersection point (t)
        float t1 = (-b - sqrtf(discriminant)) / (2.0f * a);
        float t2 = (-b + sqrtf(discriminant)) / (2.0f * a);

        // Choose the nearest t that's in front of the camera (positive t)
	float t = (t1 > 0) ? t1 : (t2 > 0 ? t2 : INFINITY);

        // If both t values are negative, the intersection is behind the camera
		//printf("Both t1 and t2 are negative, intersection behind camera\n");
		if (t < 0)
            return (false); // Intersection is behind the camera
		*hit_point = add_vector(ray_origin, (scale_vector(ray_direction, t)));
        //printf("Intersection point: (%f, %f, %f)\n", hit_point->x, hit_point->y, hit_point->z);
        return (true); // Intersection occurs
    }
}

// Function to check if a ray intersects a plane and return the intersection point
// No Quadratic Equation: Unlike the sphere and cylinder cases, which lead to quadratic equations 
// with potential multiple intersection points (hence the need for a discriminant), the ray-plane intersection 
// resolves directly into a linear equation. The result gives a single value for 𝑡, 
// which tells us the distance along the ray to the intersection point.

// Parallel Ray Check: The check for denom = n \cdot D (the dot product of the plane's normal and the ray's direction) 
// serves to determine if the ray is parallel to the plane. 
// If denom is close to zero, it indicates that the ray is parallel and will never intersect with the plane, 
// similar to checking if the discriminant is negative for spheres or cylinders.
bool ray_plane_intersection(t_plane plane, t_vec3d ray_origin, t_vec3d ray_direction, t_vec3d *hit_point)
{
// If denom is 0, it means the ray is parallel to the plane. In this case, there won't be an intersection since the ray will never cross the plane.
// If denom is greater than 0, it indicates that the ray is moving towards the plane (if the normal points outward).
// If denom is less than 0, it indicates that the ray is moving away from the plane.
    // Dot product between ray direction and the plane normal
	float	denom;

    // If denom is close to 0, the ray is parallel to the plane, so no intersection
	denom = dot_product(ray_direction, plane.normal);
    if (fabs(denom) > 1e-6) // Small epsilon to handle floating point inaccuracies
    {
        // Calculate vector from ray ray_origin to a point on the plane
        t_vec3d p0l0 = {
            plane.point.x - ray_origin.x,
            plane.point.y - ray_origin.y,
            plane.point.z - ray_origin.z
        };

        // Calculate the distance along the ray to the intersection point (t)
        float t = dot_product(p0l0, plane.normal) / denom;

        // If t is positive, the intersection point is in front of the camera
        if (t >= 0)
        {
            // Calculate the intersection point
            hit_point->x = ray_origin.x + t * ray_direction.x;
            hit_point->y = ray_origin.y + t * ray_direction.y;
            hit_point->z = ray_origin.z + t * ray_direction.z;
            return (true); // Intersection found
        }
    }
    return (false); // No intersection
}

bool ray_cylinder_intersection(t_cylinder cylinder, t_vec3d ray_origin, t_vec3d ray_direction, t_vec3d *hit_point)
{
    float radius;
	t_vec3d oc;
	float discriminant;
	radius = cylinder.diameter / 2.0f;
	oc = subtract_vector(ray_origin, cylinder.center);
    // Calculate quadratic coefficients
    float a = dot_product(ray_direction, ray_direction) - dot_product(ray_direction, cylinder.axis) * dot_product(ray_direction, cylinder.axis);
    float b = 2.0f * (dot_product(oc, ray_direction) - dot_product(oc, cylinder.axis) * dot_product(ray_direction, cylinder.axis));
    float c = dot_product(oc, oc) - dot_product(oc, cylinder.axis) * dot_product(oc, cylinder.axis) - radius * radius;

    // Calculate the discriminant
    discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return (false); // No intersection

    // Calculate the two intersection points
    float t1 = (-b - sqrtf(discriminant)) / (2.0f * a);
    float t2 = (-b + sqrtf(discriminant)) / (2.0f * a);

    // Choose the smallest positive t
    float t = (t1 > 0) ? t1 : (t2 > 0 ? t2 : INFINITY);

	if (t < 0)
		return (false); // Intersection is behind the ray ray_origin

    // Calculate the intersection point
    t_vec3d intersection;
	intersection = add_vector(ray_origin, (scale_vector(ray_direction, t)));

    // Check if the intersection point is within the height bounds of the cylinder
    t_vec3d d = {
        intersection.x - cylinder.center.x,
        intersection.y - cylinder.center.y,
        intersection.z - cylinder.center.z
    };

    // Project the distance along the cylinder axis to check if within height
	float height_projection = dot_product(d, cylinder.axis);
	if (height_projection < 0 || height_projection > cylinder.height)
		return (false); // Intersection is outside the height of the cylinder

    // Store the intersection point
    *hit_point = intersection;
    return (true); // Intersection occurs
}

bool ray_cylinder_top(t_cylinder cylinder, t_vec3d ray_origin, t_vec3d ray_direction, t_vec3d *hit_point)
{
    // Calculate top center
    t_vec3d top_center = add_vector(cylinder.center, scale_vector(cylinder.axis, cylinder.height / 2.0f));
    float radius = cylinder.diameter / 2.0f;

    // Calculate intersection with top plane
    float denom = dot_product(ray_direction, cylinder.axis);
    if (fabs(denom) < 1e-6)
		return (false); // Ray is parallel to the top cap plane

    t_vec3d to_cap = subtract_vector(top_center, ray_origin);
    float t = dot_product(to_cap, cylinder.axis) / denom;

	if (t < 0)
		return (false); // Cap intersection is behind the ray
    // Calculate exact intersection point
    t_vec3d point = add_vector(ray_origin, scale_vector(ray_direction, t));
    // Check if intersection point is within the cap radius
    t_vec3d to_point = subtract_vector(point, top_center);
    float dist2 = dot_product(to_point, to_point);
    if (dist2 <= radius * radius) {
        *hit_point = point;
        return (true); // Intersection found
    }
    return (false); // No intersection
}

bool ray_cylinder_bottom(t_cylinder cylinder, t_vec3d ray_origin, t_vec3d ray_direction, t_vec3d *hit_point)
{
	t_vec3d bottom_center;
	float radius;
	float denom;
	bottom_center = cylinder.center;
	radius = cylinder.diameter / 2.0f;
	// Calculate intersection with bottom plane
	denom = dot_product(ray_direction, cylinder.axis);
    if (fabs(denom) < 1e-6)
		return (false); // Ray is parallel to the bottom cap plane

    t_vec3d to_cap = subtract_vector(bottom_center, ray_origin);
    float t = dot_product(to_cap, cylinder.axis) / denom;

    if (t < 0)
		return (false); // Cap intersection is behind the ray
    // Calculate exact intersection point
    t_vec3d point = add_vector(ray_origin, scale_vector(ray_direction, t));

    // Check if intersection point is within the cap radius
    t_vec3d to_point = subtract_vector(point, bottom_center);
    float dist2 = dot_product(to_point, to_point);
    if (dist2 <= radius * radius)
	{
        *hit_point = point;
        return (true);
    }
    return (false);
}