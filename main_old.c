/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_old.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:29:09 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/10/09 19:59:18 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	setup_image(t_data *img)
{
	int				x;
	int				y;
	int				iteration;
	t_position		c;

	iteration = 0;
	y = -1;
	while (++y <= PIXEL)
	{
		x = -1;
		while (++x <= PIXEL)
		{
			c.a = ft_place(x + img->m_x, -2 / img->zoom, +2 / img->zoom, PIXEL);
			c.b = ft_place(y + img->m_y, +2 / img->zoom, -2 / img->zoom, PIXEL);
			iteration = setup_mandelbrot(c, img);
			ft_color(iteration, x, y, img);
		}
	}
	mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img, 0, 0);
}

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
	setup_image(img);
	return (0);
}

int	close_window(t_data *img)
{
	mlx_destroy_image(img->mlx_ptr, img->img);
	mlx_destroy_window(img->mlx_ptr, img->win_ptr);
	mlx_destroy_display(img->mlx_ptr);
	free(img->mlx_ptr);
	free(img);
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
		free(img);
		exit(0);
	}
	return (0);
}


void	setup_hooks(t_data *img)
{
	mlx_mouse_hook(img->win_ptr, ft_mousehooks, img);
	//mlx_key_hook(img->win_ptr, ft_keyhooks, img);//maybe later for keyboard instructs
	mlx_hook(img->win_ptr, ON_DESTROY, 0, close_window, img);
	mlx_hook(img->win_ptr, ON_KEYDOWN, 1, close_window_esc, img);
	mlx_loop(img->mlx_ptr);
}
double	ft_place(double value, double bottom, double top, double max)
{
	double	place;
	double	convertunit;

	convertunit = (top - bottom) / max;
	place = (value * convertunit) + bottom;
	return (place);
}

void	calculate_addr(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	red_scheme(int iteration, int x, int y, t_data *img)
{
	int		red;
	int		green;
	int		blue;
	int		color;
	double	n;

	n = (double)iteration * img->colorrange;
	red = 0;
	green = 0;
	blue = 0;
	color = 0;
	blue += (int)(img->blue * (1 - n) * n * n * n * 255);
	green += (int)(img->green * (1 - n) * (1 - n) * n * n * 255);
	red += (int)(img->red * (1 - n) * (1 - n) * (1 - n) * n * 255);
	color = (red << 16) | (green << 8) | blue;
	calculate_addr(img, x, y, color);
}

void	ft_color(int iteration, int x, int y, t_data *img)
{
	red_scheme(iteration, x, y, img);
	return ;
}

int	setup_mandelbrot(t_position c, t_data *img)
{
	t_position	value;
	int			i;
	double		c2;

	i = 0;
	c2 = c.a * c.a + c.b * c.b;
	if (256.0 * c2 * c2 - 96.0 * c2 + 32.0 * c.a - 3.0 < 0.0)
		return (img->iter);
	if (16.0 * (c2 + 2.0 * c.a + 1.0) - 1.0 < 0.0) 
		return (img->iter);
	value.a = 0;
	value.b = 0;
	while (i < img->iter)
	{
		value.x = (value.a * value.a) - (value.b * value.b);
		value.y = 2 * (value.a * value.b);
		value.x += c.a;
		value.y += c.b;
		value.a = value.x;
		value.b = value.y;
		i++;
	}
	return (i);
}


void	setup_struct(t_data **img)
{
	*img = (t_data *)malloc(sizeof(t_data));
	if (*img == NULL)
	{
		// Handle memory allocation failure if necessary
		return;
	}
	(*img)->iter = 100;
	(*img)->zoom = 1;
	(*img)->colorrange = 0.001;
	(*img)->red = 1;
	(*img)->green = 2;
	(*img)->blue = 3;
	(*img)->m_x = 0.0;
	(*img)->m_y = 0.0;
	(*img)->offset_x = 0.0;
	(*img)->offset_y = 0.0;
}


int	main(void)
{
	t_img	*img = NULL;

	setup_struct(&img);
	img->mlx_ptr = mlx_init();
	if (!img->mlx_ptr)
		print_error(1, img);
	img->win_ptr = mlx_new_window(img->mlx_ptr, PIXEL, PIXEL, "miniRT");
	if (!img->win_ptr)
		print_error(2, img);
	img->img = mlx_new_image(img->mlx_ptr, PIXEL, PIXEL);
	if (!img->img)
		print_error(3, img);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
				&img->line_length, &img->endian);
	if (!img->addr)
		print_error(4, img);
	setup_image(img);
	setup_hooks(img);
}