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
	mlx_destroy_display(img->mlx_ptr);
	free(img->mlx_ptr);
	exit(0);
}

int	close_window_esc(int keycode, t_graphic *img)
{
	if (keycode == ESC)
	{
		mlx_destroy_image(img->mlx_ptr, img->img);
		mlx_destroy_window(img->mlx_ptr, img->win_ptr);
		mlx_destroy_display(img->mlx_ptr);
		free(img->mlx_ptr);
		exit(0);
	}
	return (0);
}

void	my_mlx_pixel_put(t_graphic *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	setup_hooks(t_graphic *img)
{
	// mlx_mouse_hook(img->win_ptr, ft_mousehooks, img);
	// mlx_key_hook(img->win_ptr, ft_keyhooks, img);
	mlx_hook(img->win_ptr, ON_DESTROY, 0, close_window, img);
	mlx_hook(img->win_ptr, ON_KEYDOWN, 1, close_window_esc, img);
	mlx_loop(img->mlx_ptr);
}

void	init_mlx(t_data *data)
{
	t_graphic img;

	img.mlx_ptr = mlx_init();
	img.win_ptr = mlx_new_window(img.mlx_ptr, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(img.mlx_ptr, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(img.mlx_ptr, img.win_ptr, img.img, 0, 0);
	setup_hooks(&img);
}