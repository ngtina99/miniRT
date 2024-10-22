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
	v.x /= magnitude;
	v.y /= magnitude;
	v.z /= magnitude;
	return v;
}

// Example of ray tracing, where rays originate from (0,0,0)
void ray_trace(t_data *data, int screen_width, int screen_height)
{
	t_vec3d origin = {0.0f, 0.0f, 0.0f}; // Camera at (0, 0, 0)
	t_vec3d direction;
	int x, y;

	// Iterate over screen pixels (in this example, assume simple grid loop)
	for (y = 0; y < screen_height; y++)
	{
		for (x = 0; x < screen_width; x++)
		{
			// Calculate direction based on screen coordinates
			// Assuming the screen is centered at (0, 0), scale to [-1, 1] for both axes
			direction.x = (2.0f * x / screen_width) - 1.0f;
			direction.y = (2.0f * y / screen_height) - 1.0f;
			direction.z = -1.0f; // Send the ray "forward" in the negative z direction
			
			// Normalize the direction vector
			direction = normalize(direction);

			// Set color and render the pixel (in this case, color it red)
			int color = vector_rendering(data);
			// TODO: Render pixel with the given color
			// Example: set_pixel(x, y, color); // You'll need to implement this
		}
	}
}
