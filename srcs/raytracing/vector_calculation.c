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

int	vector_rendering(t_data *data)
{
	int color_code;

	(void)data;

			// data->red = 0;//just for test
			// data->green = 0;//just for test
			// data->blue = 255;//just for test
	
	color_code = (data->red << 16) | (data->green << 8) | data->blue;
	return(color_code);
}

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

void ray_trace(t_data *data, int x, int y, int screen_width, int screen_height)
{
    t_vec3d origin;    // Camera position
    t_vec3d direction; // Ray direction

    // Get the camera orientation as forward vector
    t_vec3d forward = {data->camera.orientation[0], data->camera.orientation[1], data->camera.orientation[2]};
    forward = normalize(forward);

    // World up vector (commonly (0, 1, 0) for a Y-up system)
    t_vec3d world_up = {0.0f, 1.0f, 0.0f};

    // Calculate the right and up vectors of the camera's orientation
    t_vec3d right = normalize(cross_product(forward, world_up));
    t_vec3d up = normalize(cross_product(right, forward));

    // Field of View and Aspect Ratio
    float aspect_ratio = (float)screen_width / screen_height;
    float fov = (float)data->camera.fov; // Use the camera's FOV value
    float scale = tan(fov * 0.5 * M_PI / 180.0f); // FOV scale factor

    // Set the camera's position as the origin of the ray
    origin.x = data->camera.position[0];
    origin.y = data->camera.position[1];
    origin.z = data->camera.position[2];

    // Calculate the pixel location in normalized device coordinates (NDC)
    float px = (2.0f * x / screen_width - 1.0f) * aspect_ratio * scale;
    float py = (1.0f - 2.0f * y / screen_height) * scale;

    // Ray direction in world space: use the camera's orientation, right, and up vectors
    direction.x = forward.x + px * right.x + py * up.x;
    direction.y = forward.y + px * right.y + py * up.y;
    direction.z = forward.z + px * right.z + py * up.z;

    // Normalize the ray direction
    direction = normalize(direction);

    // For now, color based on normalized direction
    int red   = (int)((direction.x + 1.0f) / 2.0f * 255);  // Red depends on the x-direction
    int green = (int)((direction.y + 1.0f) / 2.0f * 255);  // Green depends on the y-direction
    int blue  = (int)((direction.z + 1.0f) / 2.0f * 255);  // Blue depends on the z-direction

    // Combine colors into a color code (RGB format)
    int color_code = (red << 16) | (green << 8) | blue;

    // Place the calculated color at the pixel (x, y)
    my_mlx_pixel_put(data->img, x, y, color_code);
}

