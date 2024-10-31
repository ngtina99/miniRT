/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:28:19 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/10/31 13:45:05 by yioffe           ###   ########.fr       */
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
	t = (t1 > 0) ? t1 : t2;
	return (t);
}

bool	ray_sphere_intersection(t_sphere sphere, t_vec3d ray_origin, t_vec3d ray_direction, t_vec3d *hit_point)
{
	float	radius;
	t_vec3d	oc; //from origin to center
	float	t;

	radius = sphere.diameter / 2.0f;
	oc = subtract_vector(ray_origin, sphere.center);
	float a = dot_product(ray_direction, ray_direction);
	float b = 2.0f * dot_product(oc, ray_direction);
	float c = dot_product(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (false); // No intersection
	t = calculate_nearest_inters_p(a, b, discriminant);
	// If both t values are negative, the intersection is behind the camera
	//printf("Both t1 and t2 are negative, intersection behind camera\n");
	if (t < 0)
		return (false); // Intersection is behind the camera
	*hit_point = add_vector(ray_origin, (scale_vector(ray_direction, t)));
	//printf("Intersection point: (%f, %f, %f)\n", hit_point->x, hit_point->y, hit_point->z);
	return (true); // Intersection occurs
}

// Function to check if a ray intersects a plane and return the intersection point
// No Quadratic Equation: Unlike the sphere and cylinder cases, which lead to quadratic equations 
// with potential multiple intersection points (hence the need for a discriminant), the ray-plane intersection 
// resolves directly into a linear equation. The result gives a single value for 𝑡, 
// which tells us the distance along the ray to the intersection point.

// serves to determine if the ray is parallel to the plane. 
// If parallel_factor is close to zero, it indicates that the ray is parallel and will never intersect with the plane, 
// similar to checking if the discriminant is negative for spheres or cylinders.
bool ray_plane_intersection(t_plane plane, t_vec3d ray_origin, t_vec3d ray_direction, t_vec3d *hit_point)
{
// If parallel_factor is 0, it means the ray is parallel to the plane. In this case, there won't be an intersection since the ray will never cross the plane.
// If parallel_factor is greater than 0, it indicates that the ray is moving towards the plane (if the normal points outward).
// If parallel_factor is less than 0, it indicates that the ray is moving away from the plane.
    // Dot product between ray direction and the plane normal
	float	parallel_factor;
	t_vec3d po; //from plane to ray_origin
	float t;
    // If denom is close to 0, the ray is parallel to the plane, so no intersection
	parallel_factor = dot_product(ray_direction, plane.normal);
	if (fabs(parallel_factor) > 1e-6) // Small epsilon to handle floating point inaccuracies
	{
        // Calculate vector from ray origin to a point on the plane		
		po = subtract_vector(plane.point, ray_origin);
        // Calculate the distance along the ray to the intersection point (t)
		t = dot_product(po, plane.normal) / parallel_factor;
        // If t is positive, the intersection point is in front of the camera
        if (t >= 0)
        {
            // Calculate the intersection point
			*hit_point = add_vector(ray_origin, (scale_vector(ray_direction, t)));
            return (true); // Intersection found
        }
    }
    return (false); // No intersection
}

// bool ray_cylinder_intersection(t_cylinder cylinder, t_vec3d ray_origin, t_vec3d ray_direction, t_vec3d *hit_point)
// {
// 	float	radius;
// 	t_vec3d	oc;
// 	float	discriminant;
// 	float	t;
// 	t_vec3d	intersection;
// 	t_vec3d	diff;

// 	radius = cylinder.diameter / 2.0f;
// 	oc = subtract_vector(ray_origin, cylinder.center);
//     // Calculate quadratic coefficients
//     float a = dot_product(ray_direction, ray_direction) - dot_product(ray_direction, cylinder.axis) * dot_product(ray_direction, cylinder.axis);
//     float b = 2.0f * (dot_product(oc, ray_direction) - dot_product(oc, cylinder.axis) * dot_product(ray_direction, cylinder.axis));
//     float c = dot_product(oc, oc) - dot_product(oc, cylinder.axis) * dot_product(oc, cylinder.axis) - radius * radius;
//     // Calculate the discriminant
//     discriminant = b * b - 4 * a * c;
//     if (discriminant < 0)
//         return (false); // No intersection
//     // Calculate the two intersection points
// 	t = calculate_nearest_inters_p(a, b, discriminant);
// 	if (t < 0)
// 		return (false); // Intersection is behind the ray ray_origin
//     // Calculate the intersection point
// 	intersection = add_vector(ray_origin, (scale_vector(ray_direction, t)));
//     // Check if the intersection point is within the height bounds of the cylinder
// 	diff = (subtract_vector(intersection, cylinder.center)); // it is needed, first here for height calculation and we can only store later in hitpoint
//     // Project the distance along the cylinder axis to check if within height
// 	float height_projection = dot_product(diff, cylinder.axis);
// 	// If height_projection < 0: The point lies below the bottom cap of the cylinder.
// 	// If height_projection > cylinder.height: The point lies above the top cap of the cylinder.
// 	if (height_projection < 0 || height_projection > cylinder.height)
// 		return (false); // Intersection is outside the height of the cylinder
//     // Store the intersection point
//     *hit_point = intersection;
//     return (true); // Intersection occurs
// }


// new function - YULIA
bool ray_cylinder_intersection(t_cylinder cylinder, t_vec3d ray_origin, t_vec3d ray_direction, t_vec3d *hit_point)
{
    float   radius;
    t_vec3d oc;
    float   discriminant;
    float   t;
    t_vec3d intersection;
    t_vec3d diff;

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
    // Calculate the nearest intersection point
    t = calculate_nearest_inters_p(a, b, discriminant);
    if (t < 0)
        return (false); // Intersection is behind the ray origin
    // Calculate the intersection point
    intersection = add_vector(ray_origin, scale_vector(ray_direction, t));
    // Check if the intersection point is within the height bounds of the cylinder
    diff = subtract_vector(intersection, cylinder.center); // for height calculation and storing later in hit_point
    float height_projection = dot_product(diff, cylinder.axis);
    
    // If the intersection point is outside the height of the cylinder
    if (height_projection < 0 || height_projection > cylinder.height) {
        // Check for intersections with the top and bottom caps
        // Bottom Cap
        float parallel_factor = dot_product(ray_direction, cylinder.axis);
        if (fabs(parallel_factor) > 1e-6) { // Ensure ray is not parallel to caps
            // Bottom cap check
            t = dot_product(subtract_vector(cylinder.center, ray_origin), cylinder.axis) / parallel_factor;
            if (t >= 0) { // Intersection in front of ray origin
                intersection = add_vector(ray_origin, scale_vector(ray_direction, t));
                diff = subtract_vector(intersection, cylinder.center);
                if (dot_product(diff, diff) <= radius * radius) {
                    *hit_point = intersection;
                    return (true); // Intersection with the bottom cap
                }
            }
            // Top cap check
            t_vec3d top_center = add_vector(cylinder.center, scale_vector(cylinder.axis, cylinder.height));
            t = dot_product(subtract_vector(top_center, ray_origin), cylinder.axis) / parallel_factor;
            if (t >= 0) { // Intersection in front of ray origin
                intersection = add_vector(ray_origin, scale_vector(ray_direction, t));
                diff = subtract_vector(intersection, top_center);
                if (dot_product(diff, diff) <= radius * radius) {
                    *hit_point = intersection;
                    return (true); // Intersection with the top cap
                }
            }
        }
        return (false); // No intersection with the cylinder or caps
    }

    // Store the intersection point on the cylindrical surface
    *hit_point = intersection;
    return (true); // Intersection occurs
}



bool ray_cylinder_bottom(t_cylinder cylinder, t_vec3d ray_origin, t_vec3d ray_direction, t_vec3d *hit_point)
{
	t_vec3d	bottom_center;
	float	radius;
	float	parallel_factor; // 
	t_vec3d	bo; //from bottom to origin
	float	t;
	t_vec3d point;
	t_vec3d pb; //from point to bottom

	//subtract the half of the center to get the bottom center
	bottom_center = cylinder.center;
	radius = cylinder.diameter / 2.0f;
	// Calculate intersection with bottom plane
	parallel_factor = dot_product(ray_direction, cylinder.axis);
	//if (parallel_factor > 1e-6 || parallel_factor < -1e-6) it would be the same affect as with fabs
	if (fabs(parallel_factor) < 1e-6)
		return (false); // Ray is parallel to the bottom cap plane
	bo = subtract_vector(bottom_center, ray_origin); // check if the ray hits the bottom
	t = dot_product(bo, cylinder.axis) / parallel_factor;
	if (t < 0)
		return (false); // Cap intersection is behind the ray
    // Calculate exact intersection point
	point = add_vector(ray_origin, scale_vector(ray_direction, t));
    // Check if intersection point is within the cap radius
	pb = subtract_vector(point, bottom_center);
	// Calculating the dot product of a vector with itself, dot_product(pb, pb),
	//  gives the squared length of that vector.
	// This squared distance is a shorthand for avoiding the costly square root operation 
	// (from sqrt()), making it more efficient.
	if ((dot_product(pb, pb)) <= radius * radius)
	{
		*hit_point = point;
		return (true);
	}
	return (false);
}

bool ray_cylinder_top(t_cylinder cylinder, t_vec3d ray_origin, t_vec3d ray_direction, t_vec3d *hit_point)
{
	t_vec3d	top_center;
	float	radius;
	float parallel_factor = dot_product(ray_direction, cylinder.axis);
	t_vec3d to; //from top to origin ray
	float t;
	t_vec3d point;
	t_vec3d pt; //from point to bottom

	//ad the half height of the cylinder to get the top
	top_center = add_vector(cylinder.center, scale_vector(cylinder.axis, cylinder.height / 2.0f));
	radius = cylinder.diameter / 2.0f;
	parallel_factor = dot_product(ray_direction, cylinder.axis);
	if (fabs(parallel_factor) < 1e-6)
		return (false); // Ray is parallel to the top cap plane
	to = subtract_vector(top_center, ray_origin);
	t = dot_product(to, cylinder.axis) / parallel_factor;
	if (t < 0)
		return (false); // Cap intersection is behind the ray
    // Calculate exact intersection point
	point = add_vector(ray_origin, scale_vector(ray_direction, t));
    // Check if intersection point is within the cap radius
	pt = subtract_vector(point, top_center);
	if (dot_product(pt, pt) <= radius * radius)
	{
		*hit_point = point;
		return (true); // Intersection found
	}
	return (false); // No intersection
}
