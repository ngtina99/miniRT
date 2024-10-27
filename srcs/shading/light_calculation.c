/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_calculation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngtina1999 <ngtina1999@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:56:30 by ngtina1999        #+#    #+#             */
/*   Updated: 2024/10/27 14:57:10 by ngtina1999       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// I did not put to Makefile yet
//Function to calculate lighting for a given point
int	calculate_lighting(t_data *data, t_vec3d hit_point, t_vec3d normal)
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