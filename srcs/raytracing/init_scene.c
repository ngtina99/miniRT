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
	int		color_code;
	t_vec3d	direction;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			ray_trace(data, (int)x, (int)y);
	}
	mlx_put_image_to_window(data->img->mlx_ptr, data->img->win_ptr,
		data->img->img, 0, 0);
}
