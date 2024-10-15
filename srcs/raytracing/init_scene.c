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
			// ray = make_ray(data, make_v_dir(data, x, y));
			// ray.inter = closest_inter(data, &ray);
			// lights_shadows(data, data->sc, ray.inter);
			// data->red = 0;//just for test
			// data->green = 0;//just for test
			// data->blue = 255;//just for test
			color_code = (data->red << 16) | (data->green << 8) | data->blue;
			my_mlx_pixel_put(data->img, x, y, color_code);
		}
	}
	//my_mlx_pixel_put(data->img, 5, 5, 0x00FF0000);//just for test
	mlx_put_image_to_window(data->img->mlx_ptr, data->img->win_ptr, data->img->img, 0, 0);
}