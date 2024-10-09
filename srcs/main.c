/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:49:19 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/10/09 20:20:11 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// int	main(void)
// {
// 	void	*img;
// 	void	*mlx;

// 	mlx = mlx_init();
// 	img = mlx_new_image(mlx, 1920, 1080);
// }

// void	init_window(t_display *disp, t_settings *settings)
// {
// 	disp->mlx = mlx_init();
// 	if (disp->mlx == NULL)
// 		return ;
// 	open one window
// 	render, edit, display image as a struct part = mlx_new_image(disp->mlx, settings->render_w,
// 			settings->render_h);
//	give addr for it too;
// 	disp->bpp /= 8;
// }

void	init_data(t_data *scene)
{
	//width, height, scales, other infos from RT FILE
}

// void	setup_hooks(t_scene *data)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data->count.shapes && data->shapes[i].type == PLANE)
// 		i++;
// 	if (i == data->count.shapes && data->count.shapes > 0)
// 	{
// 		data->shapes[0].props.highlighted = false;
// 		data->shape_idx = -1;
// 	}
// 	else if (data->shapes[i].type != PLANE && data->count.shapes > 0)
// 	{
// 		data->shapes[i].props.highlighted = true;
// 		data->shape_idx = i;
// 	}
// 	mlx_hook(data->disp->win, 2, (1L << 0), key_press, data);
// 	mlx_hook(data->disp->win, 3, (1L << 1), key_release, data);
// 	mlx_hook(data->disp->win, 4, (1L << 2), mouse_down, data);
// 	mlx_hook(data->disp->win, 5, (1L << 3), mouse_up, data);
// 	mlx_hook(data->disp->win, 17, 0, close_window, data);
// 	mlx_loop_hook(data->disp->mlx, render_loop, data);
// }
// • If any misconfiguration of any kind is encountered in the file the program must exit
// properly and return "Error\n" followed by an explicit error message of your choice.


int	main(int argc, char **argv)
{
	//t_data		*data;
	t_graphic	img;
	int			fd;

	if (argc != 2)
	{
		printf(RED"Error: input number has to be one\n"RESET);
		return (-1);
	}
	fd = open_rt(argc, argv);
	if (fd == -1)
		return (EXIT_FAILURE);	
	//data = parse_rt(fd);
	// if (data == NULL)
	//  	free_data with some Error\n message and exit;
	//init_data(&data); or in parse_rt if we can set up everything
	close(fd);

	//PUT THIS IN A FUNCTION
	// img->mlx_ptr = mlx_init();
	// if (!img->mlx_ptr)
	// 	print_error(1, img);
	// if (img->set == 1)
	// 	img->win_ptr = mlx_new_window(img->mlx_ptr, \
	// 	PIXEL, PIXEL, "miniRT");
	// else if (img->set == 2)
	// 	img->win_ptr = mlx_new_window(img->mlx_ptr, PIXEL, PIXEL, "Julia");
	// else if (img->set == 3)
	// 	img->win_ptr = mlx_new_window(img->mlx_ptr, PIXEL, PIXEL, "Tricorn");
	// if (!img->win_ptr)
	// 	print_error(2, img);
	// img->img = mlx_new_image(img->mlx_ptr, PIXEL, PIXEL);
	// if (!img->img)
	// 	print_error(3, img);
	// img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
	// 			&img->line_length, &img->endian);
	// if (!img->addr)
	// 	print_error(4, img);
	// setup_image(img);
	// ft_hooks(img);
	// or do this data->img = &img;//REVERSED, CONNECT DATA TO IMAGE
	// make the scene
}