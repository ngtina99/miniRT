/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:29:09 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/09/26 18:39:04 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	print_message(int message_type)
{
	if (message_type == 1)
	{
		ft_printf("\033[1;36mPlease enter one of the following:\n");
		ft_printf("\033[1;36m➡️ ./fractol Mandelbrot\n");
		ft_printf("\033[1;36m➡️ ./fractol Julia <number> <number>\n");
		ft_printf("\033[1;36m➡️ ./fractol Tricorn\n\n");
		ft_printf("\033[1;31mRules for <number> args:\n");
		ft_printf("\033[1;31m- It has to be decimal number\n\n");
		ft_printf("\033[1;31m- Can't be smaller than -2.0\n");
		ft_printf("\033[1;31m- Can't be bigger than 2.0\n\n");
		ft_printf("\033[1;105m🤫👉tips for <number> args\n");
		ft_printf("\033[1;105m-0.4 0.6; 0.28 0.008; -0.835 -0.2321\033[0;0m");
	}
	exit (1);
}

void	print_error(int error_type, t_data *img)
{
	ft_printf("\033[1;31mMALLOC ERROR\n");
	if (error_type == 2)
	{
		mlx_loop_end(img->mlx_ptr);
		mlx_destroy_display(img->mlx_ptr);
		free(img->mlx_ptr);
	}
	else if (error_type == 3)
	{
		mlx_destroy_window(img->mlx_ptr, img->win_ptr);
		mlx_destroy_display(img->mlx_ptr);
		free(img->mlx_ptr);
	}
	else if (error_type == 4)
	{
		mlx_destroy_image(img->mlx_ptr, img->img);
		mlx_destroy_window(img->mlx_ptr, img->win_ptr);
		mlx_destroy_display(img->mlx_ptr);
		free(img->mlx_ptr);
	}
	exit (1);
}

int	ft_mousehooks(int button, int x, int y, t_data *img)
{
	img->offset_x = (x - (PIXEL / 2)) * 0.1;
	img->offset_y = (y - (PIXEL / 2)) * 0.1;
	if (button == ON_MOUSEDOWN)
	{
		img->m_x = img->m_x * 1.1 + img->offset_x;
		img->m_y = img->m_y * 1.1 + img->offset_y;
		img->zoom *= 1.1;
	}
	if (button == ON_MOUSEUP)
	{
		img->m_x = img->m_x / 1.1 + img->offset_x;
		img->m_y = img->m_y / 1.1 + img->offset_y;
		img->zoom /= 1.1;
	}
	//setup_image(img);
	return (0);
}

int	close_window(t_data *img)
{
	mlx_destroy_image(img->mlx_ptr, img->img);
	mlx_destroy_window(img->mlx_ptr, img->win_ptr);
	mlx_destroy_display(img->mlx_ptr);
	free(img->mlx_ptr);
	exit(0);
}

int	close_window_esc(int keycode, t_data *img)
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


void	ft_hooks(t_data *img)
{
	mlx_mouse_hook(img->win_ptr, ft_mousehooks, img);
	//mlx_key_hook(img->win_ptr, ft_keyhooks, img);//maybe later for keyboard instructs
	mlx_hook(img->win_ptr, ON_DESTROY, 0, close_window, img);
	mlx_hook(img->win_ptr, ON_KEYDOWN, 1, close_window_esc, img);
	mlx_loop(img->mlx_ptr);
}

int	main(void)
{
	t_data	*img = NULL;

	img->arg2 = 0.0;
	img->arg3 = 0.0;
	img->set = 1;
	//setup_struct(img);
	img->mlx_ptr = mlx_init();
	if (!img->mlx_ptr)
		print_error(1, img);
	if (img->set == 1)
		img->win_ptr = mlx_new_window(img->mlx_ptr, \
		PIXEL, PIXEL, "Mandelbrot");
	if (!img->win_ptr)
		print_error(2, img);
	img->img = mlx_new_image(img->mlx_ptr, PIXEL, PIXEL);
	if (!img->img)
		print_error(3, img);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
				&img->line_length, &img->endian);
	if (!img->addr)
		print_error(4, img);
	//setup_image(img);
	ft_hooks(img);
}