/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngtina1999 <ngtina1999@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:28:19 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/11/05 02:04:39 by ngtina1999       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_vec3d	setup_camera(t_data *data, int x, int y)
{
	t_vec3d	forward;
	t_vec3d	world_up;
	t_vec3d	right;
	t_vec3d	up;
	float	aspect_ratio;
	float	scale;
	float	px;
	float	py;
	t_vec3d result_direction;
	// Camera forward vector and its normalization
	forward = normalize(data->camera.orientation);
    // Calculate the right and up vectors for the camera's orientation
	world_up = (t_vec3d){0.0f, 1.0f, 0.0f};
	right = normalize(cross_product(forward, world_up));
	up = normalize(cross_product(right, forward));

    // Field of view and aspect ratio scaling
	aspect_ratio = (float)WIDTH / HEIGHT;
	scale = tan(data->camera.fov * 0.5 * M_PI / 180.0f);

    // Camera position as ray origin

    // Calculate the ray direction for each pixel
	px = (2.0f * x / WIDTH - 1.0f) * aspect_ratio * scale;
	py = (1.0f - 2.0f * y / HEIGHT) * scale;
	result_direction.x = forward.x + px * right.x + py * up.x;
	result_direction.y = forward.y + px * right.y + py * up.y;
	result_direction.z = forward.z + px * right.z + py * up.z;
	return(normalize(result_direction));
}