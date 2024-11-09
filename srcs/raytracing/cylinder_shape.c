/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_shape.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 01:32:47 by ngtina1999        #+#    #+#             */
/*   Updated: 2024/11/09 15:05:23 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool ray_cylinder_intersection(t_cylinder cylinder, t_vec3d ray_origin, t_vec3d ray_direction, t_vec3d *hit_point)
{
    float radius = cylinder.diameter / 2.0f;
    t_vec3d oc = subtract_vector(ray_origin, cylinder.center);

    // Ensure the cylinder axis is normalized
    t_vec3d cylinder_axis = normalize(cylinder.axis);

    // Decompose ray direction into parallel and perpendicular components to the cylinder axis
    float ray_dir_parallel = dot_product(ray_direction, cylinder_axis);
    t_vec3d ray_dir_perp = subtract_vector(ray_direction, scale_vector(cylinder_axis, ray_dir_parallel));

    // Decompose oc into parallel and perpendicular components to the cylinder axis
    float oc_parallel = dot_product(oc, cylinder_axis);
    t_vec3d oc_perp = subtract_vector(oc, scale_vector(cylinder_axis, oc_parallel));

    // Calculate quadratic coefficients based on perpendicular components
    float a = dot_product(ray_dir_perp, ray_dir_perp);
    float b = 2.0f * dot_product(oc_perp, ray_dir_perp);
    float c = dot_product(oc_perp, oc_perp) - radius * radius;

    // Calculate discriminant
    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return false; // No intersection with the infinite cylinder

    // Calculate the nearest intersection point (t)
    float t = calculate_nearest_inters_p(a, b, discriminant);
    if (t < 0)
        return false; // Intersection is behind the ray origin

    // Calculate the intersection point in 3D space
    t_vec3d intersection = add_vector(ray_origin, scale_vector(ray_direction, t));

    // Check if the intersection point is within the cylinder height bounds
    t_vec3d diff = subtract_vector(intersection, cylinder.center);
    float height_projection = dot_product(diff, cylinder_axis);

    if (height_projection < 0 || height_projection > cylinder.height)
        return false; // Intersection is outside the height bounds of the cylinder

    // If within height, store the intersection point
    *hit_point = intersection;
    return true; // Intersection occurs
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
	bottom_center = subtract_vector(cylinder.center, scale_vector(cylinder.axis, 0.0001f));
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

// a bit changed original function to include tops and bottoms - YULIA
// bool ray_cylinder_intersection(t_cylinder cylinder, t_vec3d ray_origin, t_vec3d ray_direction, t_vec3d *hit_point)
// {
//     float   radius;
//     t_vec3d oc;
//     float   discriminant;
//     float   t;
//     t_vec3d intersection;
//     t_vec3d diff;

//     radius = cylinder.diameter / 2.0f;
//     oc = subtract_vector(ray_origin, cylinder.center);
//     // Calculate quadratic coefficients
//     float a = dot_product(ray_direction, ray_direction) - dot_product(ray_direction, cylinder.axis) * dot_product(ray_direction, cylinder.axis);
//     float b = 2.0f * (dot_product(oc, ray_direction) - dot_product(oc, cylinder.axis) * dot_product(ray_direction, cylinder.axis));
//     float c = dot_product(oc, oc) - dot_product(oc, cylinder.axis) * dot_product(oc, cylinder.axis) - radius * radius;
//     // Calculate the discriminant
//     discriminant = b * b - 4 * a * c;
//     if (discriminant < 0)
//         return (false); // No intersection
//     // Calculate the nearest intersection point
//     t = calculate_nearest_inters_p(a, b, discriminant);
//     if (t < 0)
//         return (false); // Intersection is behind the ray origin
//     // Calculate the intersection point
//     intersection = add_vector(ray_origin, scale_vector(ray_direction, t));
//     // Check if the intersection point is within the height bounds of the cylinder
//     diff = subtract_vector(intersection, cylinder.center); // for height calculation and storing later in hit_point
//     float height_projection = dot_product(diff, cylinder.axis);
    
//     // If the intersection point is outside the height of the cylinder
//     if (height_projection < 0 || height_projection > cylinder.height) {
//         // Check for intersections with the top and bottom caps
//         // Bottom Cap
//         float parallel_factor = dot_product(ray_direction, cylinder.axis);
//         if (fabs(parallel_factor) > 1e-6) { // Ensure ray is not parallel to caps
//             // Bottom cap check
//             t = dot_product(subtract_vector(cylinder.center, ray_origin), cylinder.axis) / parallel_factor;
//             if (t >= 0) { // Intersection in front of ray origin
//                 intersection = add_vector(ray_origin, scale_vector(ray_direction, t));
//                 diff = subtract_vector(intersection, cylinder.center);
//                 if (dot_product(diff, diff) <= radius * radius) {
//                     *hit_point = intersection;
//                     return (true); // Intersection with the bottom cap
//                 }
//             }
//             // Top cap check
//             t_vec3d top_center = add_vector(cylinder.center, scale_vector(cylinder.axis, cylinder.height));
//             t = dot_product(subtract_vector(top_center, ray_origin), cylinder.axis) / parallel_factor;
//             if (t >= 0) { // Intersection in front of ray origin
//                 intersection = add_vector(ray_origin, scale_vector(ray_direction, t));
//                 diff = subtract_vector(intersection, top_center);
//                 if (dot_product(diff, diff) <= radius * radius) {
//                     *hit_point = intersection;
//                     return (true); // Intersection with the top cap
//                 }
//             }
//         }
//         return (false); // No intersection with the cylinder or caps
//     }

//     // Store the intersection point on the cylindrical surface
//     *hit_point = intersection;
//     return (true); // Intersection occurs
// }