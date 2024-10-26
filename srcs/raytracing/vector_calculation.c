/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_calculation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:28:19 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/10/17 17:28:19 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// 1. Sub-problem (Points in 3D Space)
// Requirement: to represent vectors

// Create a 3D vector struct that support following operations:

// Vector Addition
// Vector Subtraction
// Vector Magnitude
// Dot Product
// Vector Normalization
// Vector Multiplication (Multiplying a Vector by a scalar)

// int	vector_rendering(t_data *data)
// {
// 	int color_code;

// 	(void)data;

// 			// data->red = 0;//just for test
// 			// data->green = 0;//just for test
// 			// data->blue = 255;//just for test
	
// 	color_code = (data->red << 16) | (data->green << 8) | data->blue;
// 	return(color_code);
// }



// Function to normalize the direction vector
t_vec3d normalize(t_vec3d v)
{
	float magnitude = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);

	if (magnitude == 0.0f)
        return (t_vec3d){0.0f, 0.0f, -1.0f};
	v.x /= magnitude;
	v.y /= magnitude;
	v.z /= magnitude;
	return v;
}

t_vec3d cross_product(t_vec3d v1, t_vec3d v2)
{
    t_vec3d result;
    result.x = v1.y * v2.z - v1.z * v2.y;
    result.y = v1.z * v2.x - v1.x * v2.z;
    result.z = v1.x * v2.y - v1.y * v2.x;
    return (result);
}

// Function to calculate the dot product of two 3D vectors
float dot_product(t_vec3d v1, t_vec3d v2)
{
    return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

// Function to calculate the Euclidean distance between two points in 3D space
float calculate_distance(t_vec3d point1, t_vec3d point2)
{
    return sqrtf(
        (point2.x - point1.x) * (point2.x - point1.x) +
        (point2.y - point1.y) * (point2.y - point1.y) +
        (point2.z - point1.z) * (point2.z - point1.z)
    );
}


// Function to calculate lighting for a given point
int calculate_lighting(t_data *data, t_vec3d hit_point, t_vec3d normal)
{
    // Position of the light source
    t_vec3d light_pos = data->light.position;

    // Light direction: from the hit point to the light source
    t_vec3d light_dir = {
        light_pos.x - hit_point.x,
        light_pos.y - hit_point.y,
        light_pos.z - hit_point.z
    };
    light_dir = normalize(light_dir);

    // Lighting intensity (depends on the cosine of the angle between normal and light direction)
    float intensity = fmax(0.0f, dot_product(normal, light_dir)) * data->light.brightness;

    // Adding ambient light contribution
    float ambient_intensity = data->ambient.ratio;

    // Combine the ambient and direct lighting intensities
    float final_intensity = ambient_intensity + intensity;

    // Cap the final intensity to 1.0 (to avoid over-brightness)
    if (final_intensity > 1.0f) final_intensity = 1.0f;

    // Light color (scale by final intensity)
    int red   = (int)(data->light.color.red * final_intensity);
    int green = (int)(data->light.color.green * final_intensity);
    int blue  = (int)(data->light.color.blue * final_intensity);

    // Return the color as an RGB code
    return (red << 16) | (green << 8) | blue;
}

// Function to calculate normal for a sphere at a given hit point
t_vec3d calculate_normal(t_sphere sphere, t_vec3d hit_point)
{
    t_vec3d normal = {
        hit_point.x - sphere.center.x,
        hit_point.y - sphere.center.y,
        hit_point.z - sphere.center.z
    };
    return normalize(normal);
}


float get_sphere_radius(t_sphere sphere)
{
    return sphere.diameter / 2.0f;
}

int ray_sphere_intersection(t_sphere sphere, t_vec3d origin, t_vec3d direction, t_vec3d *hit_point)
{
    float radius = get_sphere_radius(sphere);
    t_vec3d oc = {
        origin.x - sphere.center.x,
        origin.y - sphere.center.y,
        origin.z - sphere.center.z
    };

    float a = dot_product(direction, direction);
    float b = 2.0f * dot_product(oc, direction);
    float c = dot_product(oc, oc) - radius * radius;

    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
    {
        return 0; // No intersection
    }
    else
    {
        // Calculate the nearest intersection point (t)
        float t1 = (-b - sqrtf(discriminant)) / (2.0f * a);
        float t2 = (-b + sqrtf(discriminant)) / (2.0f * a);

        // Choose the nearest t that's in front of the camera (positive t)
        float t = (t1 > 0) ? t1 : t2;

        // If both t values are negative, the intersection is behind the camera
        if (t < 0)
        {
            //printf("Both t1 and t2 are negative, intersection behind camera\n");
            return 0; // Intersection is behind the camera
        }

        hit_point->x = origin.x + t * direction.x;
        hit_point->y = origin.y + t * direction.y;
        hit_point->z = origin.z + t * direction.z;

        //printf("Intersection point: (%f, %f, %f)\n", hit_point->x, hit_point->y, hit_point->z);
        return 1; // Intersection occurs
    }
}

// Function to check if a ray intersects a plane and return the intersection point
int ray_plane_intersection(t_plane plane, t_vec3d origin, t_vec3d direction, t_vec3d *hit_point)
{
    // Dot product between ray direction and the plane normal
    float denom = dot_product(direction, plane.normal);

    // If denom is close to 0, the ray is parallel to the plane, so no intersection
    if (fabs(denom) > 1e-6) // Small epsilon to handle floating point inaccuracies
    {
        // Calculate vector from ray origin to a point on the plane
        t_vec3d p0l0 = {
            plane.point.x - origin.x,
            plane.point.y - origin.y,
            plane.point.z - origin.z
        };

        // Calculate the distance along the ray to the intersection point (t)
        float t = dot_product(p0l0, plane.normal) / denom;

        // If t is positive, the intersection point is in front of the camera
        if (t >= 0)
        {
            // Calculate the intersection point
            hit_point->x = origin.x + t * direction.x;
            hit_point->y = origin.y + t * direction.y;
            hit_point->z = origin.z + t * direction.z;

            return 1; // Intersection found
        }
    }

    return 0; // No intersection
}

int ray_cylinder_intersection(t_cylinder cylinder, t_vec3d ray_origin, t_vec3d ray_direction, t_vec3d *hit_point) {
    float radius = cylinder.diameter / 2.0f;
    t_vec3d oc = {
        ray_origin.x - cylinder.center.x,
        ray_origin.y - cylinder.center.y,
        ray_origin.z - cylinder.center.z
    };

    // Calculate quadratic coefficients
    float a = dot_product(ray_direction, ray_direction) - dot_product(ray_direction, cylinder.axis) * dot_product(ray_direction, cylinder.axis);
    float b = 2.0f * (dot_product(oc, ray_direction) - dot_product(oc, cylinder.axis) * dot_product(ray_direction, cylinder.axis));
    float c = dot_product(oc, oc) - dot_product(oc, cylinder.axis) * dot_product(oc, cylinder.axis) - radius * radius;

    // Calculate the discriminant
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return 0; // No intersection
    }

    // Calculate the two intersection points
    float t1 = (-b - sqrtf(discriminant)) / (2.0f * a);
    float t2 = (-b + sqrtf(discriminant)) / (2.0f * a);

    // Choose the smallest positive t
    float t = (t1 > 0) ? t1 : (t2 > 0 ? t2 : INFINITY);
    
    if (t < 0) {
        return 0; // Intersection is behind the ray origin
    }

    // Calculate the intersection point
    t_vec3d intersection = { 
        ray_origin.x + t * ray_direction.x,
        ray_origin.y + t * ray_direction.y,
        ray_origin.z + t * ray_direction.z 
    };

    // Check if the intersection point is within the height bounds of the cylinder
    t_vec3d d = { 
        intersection.x - cylinder.center.x,
        intersection.y - cylinder.center.y,
        intersection.z - cylinder.center.z 
    };

    // Project the distance along the cylinder axis to check if within height
    float height_projection = dot_product(d, cylinder.axis);
    if (height_projection < 0 || height_projection > cylinder.height) {
        return 0; // Intersection is outside the height of the cylinder
    }

    // Store the intersection point
    *hit_point = intersection;
    return 1; // Intersection occurs
}

// Function to find the closest intersection with any object (spheres and planes)
int find_closest_object(t_data *data, t_vec3d origin, t_vec3d direction, t_vec3d *closest_hit_point, int *object_type, int *object_index)
{
    int i = 0;
    float min_distance = INFINITY; // Initially set the minimum distance to infinity
    t_vec3d hit_point;
    int hit = 0;  // Flag to check if any intersection occurs

    //Check all spheres for intersection
    while (i < data->sphere_count)
    {
        if (ray_sphere_intersection(data->spheres[i], origin, direction, &hit_point))
        {
            float distance = calculate_distance(origin, hit_point);
            if (distance < min_distance)
            {
                min_distance = distance;
                *closest_hit_point = hit_point;
                *object_type = 1; // Sphere
                *object_index = i;
                hit = 1;
            }
        }
        i++;
    }

    //Check all planes for intersection
    i = 0;
    while (i < data->plane_count)
    {
        if (ray_plane_intersection(data->planes[i], origin, direction, &hit_point))
        {
            float distance = calculate_distance(origin, hit_point);
            if (distance < min_distance)
            {
                min_distance = distance;
                *closest_hit_point = hit_point;
                *object_type = 2; // Plane
                *object_index = i;
                hit = 1;
            }
        }
        i++;
    }

    i = 0;
    while (i < data->cylinder_count)
    {
        if (ray_cylinder_intersection(data->cylinders[i], origin, direction, &hit_point))
        {
            float distance = calculate_distance(origin, hit_point);
            if (distance < min_distance)
            {
                min_distance = distance;
                *closest_hit_point = hit_point;
                *object_type = 3; // cylinder
                *object_index = i;
                hit = 1;
            }
        }
        i++;
    }

    return hit; // Return whether any intersection was found
}

int convert_rgb_to_int(t__color_rgb color)
{
    int color_code;
    int red = color.red;   // Red component
    int green = color.green; // Green component
    int blue = color.blue;  // Blue component
    
    color_code = (red << 16) | (green << 8) | blue;

    return (color_code);
}

void ray_trace(t_data *data, int x, int y, int screen_width, int screen_height)
{
    t_vec3d origin;    // Camera position
    t_vec3d direction; // Ray direction

    // Camera forward vector and its normalization
    t_vec3d forward = data->camera.orientation;
    forward = normalize(forward);

    // Calculate the right and up vectors for the camera's orientation
    t_vec3d world_up = {0.0f, 1.0f, 0.0f};
    t_vec3d right = normalize(cross_product(forward, world_up));
    t_vec3d up = normalize(cross_product(right, forward));

    // Field of view and aspect ratio scaling
    float aspect_ratio = (float)screen_width / screen_height;
    float scale = tan(data->camera.fov * 0.5 * M_PI / 180.0f);

    // Camera position as ray origin
    origin = data->camera.position;

    // Calculate the ray direction for each pixel
    float px = (2.0f * x / screen_width - 1.0f) * aspect_ratio * scale;
    float py = (1.0f - 2.0f * y / screen_height) * scale;

    direction.x = forward.x + px * right.x + py * up.x;
    direction.y = forward.y + px * right.y + py * up.y;
    direction.z = forward.z + px * right.z + py * up.z;

    direction = normalize(direction);

    // Find the closest intersection among all objects (spheres and planes)
    t_vec3d closest_hit_point;
    int object_type;
    int object_index;
    if (find_closest_object(data, origin, direction, &closest_hit_point, &object_type, &object_index))
    {
        // If it's a sphere, set the color of the sphere
        if (object_type == 1) // Sphere
        {
            int color_code = convert_rgb_to_int(data->spheres[object_index].color);
            my_mlx_pixel_put(data->img, x, y, color_code);
        }
        // If it's a plane, set the color of the plane
        else if (object_type == 2) // Plane
        {
            int color_code = convert_rgb_to_int( data->planes[object_index].color);
            my_mlx_pixel_put(data->img, x, y, color_code);
        }
        else if (object_type == 3) // Plane
        {
            int color_code = convert_rgb_to_int( data->cylinders[object_index].color);
            my_mlx_pixel_put(data->img, x, y, color_code);
        }
    }
    else
    {
        // No intersection: set background color (ambient light)
        int ambient_color = (int)(255 * data->ambient.ratio);
        int color_code = (ambient_color << 16) | (ambient_color << 8) | ambient_color;
        my_mlx_pixel_put(data->img, x, y, color_code);
    }
}

   
