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
    return result;
}

// Function to calculate the dot product of two 3D vectors
float dot_product(t_vec3d v1, t_vec3d v2)
{
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

// Function to calculate lighting for a given point
// Function to calculate lighting for a given point
int calculate_lighting(t_data *data, t_vec3d hit_point, t_vec3d normal)
{
    // Position of the light source
    t_vec3d light_pos = {data->light.position[0], data->light.position[1], data->light.position[2]};

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
    int red   = (int)(data->light.color[0] * final_intensity);
    int green = (int)(data->light.color[1] * final_intensity);
    int blue  = (int)(data->light.color[2] * final_intensity);

    // Return the color as an RGB code
    return (red << 16) | (green << 8) | blue;
}

// Function to calculate normal for a sphere at a given hit point
t_vec3d calculate_normal(t_sphere sphere, t_vec3d hit_point)
{
    t_vec3d normal = {
        hit_point.x - sphere.center[0],
        hit_point.y - sphere.center[1],
        hit_point.z - sphere.center[2]
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
        origin.x - sphere.center[0],
        origin.y - sphere.center[1],
        origin.z - sphere.center[2]
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

// Function to find the closest intersection with any sphere
int find_closest_sphere(t_data *data, t_vec3d origin, t_vec3d direction, t_vec3d *closest_hit_point, int *closest_sphere_index)
{
    int i = 0;
    float min_distance = INFINITY; // Initially set the minimum distance to infinity
    t_vec3d hit_point;
    int hit = 0;  // Flag to check if any intersection occurs

    // Loop through all spheres in the scene
    while (i < data->sphere_count)
    {
        // Check if the ray intersects the current sphere
        if (ray_sphere_intersection(data->spheres[i], origin, direction, &hit_point))
        {
            // Calculate the distance from the origin to the hit point
            float distance = sqrtf(
                (hit_point.x - origin.x) * (hit_point.x - origin.x) +
                (hit_point.y - origin.y) * (hit_point.y - origin.y) +
                (hit_point.z - origin.z) * (hit_point.z - origin.z));

            // If this is the closest intersection so far, update the closest sphere
            if (distance < min_distance)
            {
                min_distance = distance;
                *closest_hit_point = hit_point;
                *closest_sphere_index = i;
                hit = 1;  // Mark that an intersection was found
            }
        }
        i++;  // Move to the next sphere
    }
    return hit;  // Return whether any intersection was found
}

int convert_rgb_to_int(int color[3])
{
    int red = color[0];   // Red component
    int green = color[1]; // Green component
    int blue = color[2];  // Blue component
    int color_code = (red << 16) | (green << 8) | blue;

    return color_code;
}

void ray_trace(t_data *data, int x, int y, int screen_width, int screen_height)
{
    t_vec3d origin;    // Camera position
    t_vec3d direction; // Ray direction

    // Camera forward vector and its normalization
    t_vec3d forward = {data->camera.orientation[0], data->camera.orientation[1], data->camera.orientation[2]};
    forward = normalize(forward);

    // Calculate the right and up vectors for the camera's orientation
    t_vec3d world_up = {0.0f, 1.0f, 0.0f};
    t_vec3d right = normalize(cross_product(forward, world_up));
    t_vec3d up = normalize(cross_product(right, forward));

    // Field of view and aspect ratio scaling
    float aspect_ratio = (float)screen_width / screen_height;
    float scale = tan(data->camera.fov * 0.5 * M_PI / 180.0f);

    // Camera position as ray origin
    origin.x = data->camera.position[0];
    origin.y = data->camera.position[1];
    origin.z = data->camera.position[2];

    // Calculate the ray direction for each pixel
    float px = (2.0f * x / screen_width - 1.0f) * aspect_ratio * scale;
    float py = (1.0f - 2.0f * y / screen_height) * scale;

    direction.x = forward.x + px * right.x + py * up.x;
    direction.y = forward.y + px * right.y + py * up.y;
    direction.z = forward.z + px * right.z + py * up.z;

    direction = normalize(direction);

    // Find the closest intersection among all spheres
    t_vec3d closest_hit_point;
    int closest_sphere_index;
    if (find_closest_sphere(data, origin, direction, &closest_hit_point, &closest_sphere_index))
    {
        int color_code = convert_rgb_to_int(data->spheres[closest_sphere_index].color);

        // Set the pixel color to the correct sphere's color
        my_mlx_pixel_put(data->img, x, y, color_code);
    }
    else
    {
        // No intersection: set background color (ambient light)
        int ambient_color = (int)(255 * data->ambient.ratio);
        int color_code = (ambient_color << 16) | (ambient_color << 8) | ambient_color;
        my_mlx_pixel_put(data->img, x, y, color_code);
    }
}
   
