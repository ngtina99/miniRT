/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 01:04:35 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/10/13 01:04:35 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	close_window(t_graphic *img)
{
	mlx_destroy_image(img->mlx_ptr, img->img);
	mlx_destroy_window(img->mlx_ptr, img->win_ptr);
	// TODO: remove before submission
	if (!IS_APPLE)
		mlx_destroy_display(img->mlx_ptr);
	free(img->mlx_ptr);
	free_scene(&img->data);
	exit(0);
}

int	close_window_esc(int keycode, t_graphic *img)
{
	if (keycode == ESC)
	{
		mlx_destroy_image(img->mlx_ptr, img->img);
		mlx_destroy_window(img->mlx_ptr, img->win_ptr);
		if (!IS_APPLE)
			mlx_destroy_display(img->mlx_ptr);
		free(img->mlx_ptr);
		free_scene(&img->data);
		exit(0);
	}
	return (0);
}

void	setup_hooks(t_graphic *img)
{
	mlx_hook(img->win_ptr, ON_DESTROY, 0, close_window, img);
	mlx_hook(img->win_ptr, 17, 0, close_window, img);
	mlx_hook(img->win_ptr, ON_KEYDOWN, 1, close_window_esc, img);
	mlx_loop(img->mlx_ptr);
}

void	init_mlx(t_data *data)
{
	t_graphic	img;

	img.mlx_ptr = mlx_init();
	img.win_ptr = mlx_new_window(img.mlx_ptr, WIDTH, HEIGHT, "miniRT");
	img.img = mlx_new_image(img.mlx_ptr, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	data->img = &img;
	init_scene_img(data);
	img.data = data;
	setup_hooks(&img);
}
