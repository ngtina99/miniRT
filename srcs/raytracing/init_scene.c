/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 03:41:42 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/10/13 03:41:42 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	init_scene_img(t_data *data)
{
	double	x;
	double	y;
	int	color_code;
	//t_ray	ray;
	t_vec3d	direction;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			// RAY DIRECTION
			// OBJECTS IN THE WAY
			// COLOR
			// SHADING
			// ray = make_ray(data, make_v_dir(data, x, y)); get a direction of the camera
			// ray.inter = closest_inter(data, &ray); it could be already calculate the color
			// lights_shadows(data, data->sc, ray.inter);
			// data->red = 0;//just for test
			// data->green = 0;//just for test
			// data->blue = 255;//just for test
			// Calculate ray direction based on screen coordinates
			direction.x = (2.0f * x / WIDTH) - 1.0f;
			direction.y = (2.0f * y / HEIGHT) - 1.0f;
			direction.z = -1.0f; // Assume ray goes "forward" in negative Z direction

			// Normalize the direction vector
			direction = normalize(direction);

			// For now, color all pixels red (set data->red = 255, green and blue to 0)
			// data->red = 0;
			// data->green = 0;
			// data->blue = 0;

			data->red = (int)((direction.x + 1.0f) / 2.0f * 255);
			data->green = (int)((direction.y + 1.0f) / 2.0f * 255);  // Modulate green based on y-direction
			data->blue = (int)((direction.z + 1.0f) / 2.0f * 255);   // Modulate blue based on z-direction

			color_code = vector_rendering(data);
			my_mlx_pixel_put(data->img, x, y, color_code);// just put the calculated color_code here
		}
	}
	//my_mlx_pixel_put(data->img, 5, 5, 0x00FF0000);//just for test
	mlx_put_image_to_window(data->img->mlx_ptr, data->img->win_ptr, data->img->img, 0, 0);
}