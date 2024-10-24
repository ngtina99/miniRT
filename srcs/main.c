/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:49:19 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/10/24 14:17:34 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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

// void	init_data(t_data *scene)
// {
// 	//width, height, scales, other infos from RT FILE
// }

// void	setup_hooks(t_data *data)
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

// FOR PARSING TESTING ONLY

void print_ambient(t_ambient *ambient) {
    printf("Ambient light: ratio = %f, color = %d,%d,%d\n", ambient->ratio, ambient->color.red, ambient->color.green, ambient->color.blue);
}

void print_camera(t_camera *camera) {
    printf("Camera: position = %f,%f,%f, orientation = %f,%f,%f, FOV = %d\n", 
            camera->position.x, camera->position.y, camera->position.z,
            camera->orientation.x, camera->orientation.y, camera->orientation.z,
            camera->fov);
}

void print_light(t_light *light) {
    printf("Light: position = %f,%f,%f, brightness = %f, color = %d,%d,%d\n", 
            light->position.x, light->position.y, light->position.z, 
            light->brightness, light->color->red, light->color->green, light->color->blue);
}

void print_spheres(t_data *scene) {
    printf("Spheres:\n");
    for (int i = 0; i < scene->sphere_count; i++) {
        t_sphere *sphere = &scene->spheres[i];
        printf("  Sphere %d: center = %f,%f,%f, diameter = %f, color = %d,%d,%d\n", i+1,
               sphere->center.x, sphere->center.y, sphere->center.z,
               sphere->diameter, sphere->color->red, sphere->color->green, sphere->color->blue);
    }
}

void print_planes(t_data *scene) {
    printf("Planes:\n");
    for (int i = 0; i < scene->plane_count; i++) {
        t_plane *plane = &scene->planes[i];
        printf("  Plane %d: point = %f,%f,%f, normal = %f,%f,%f, color = %d,%d,%d\n", i+1,
               plane->point.x, plane->point.y, plane->point.z,
               plane->normal.x, plane->normal.y, plane->normal.z,
               plane->color.red, plane->color.green, plane->color.blue);
    }
}

void print_cylinders(t_data *scene) {
    printf("Cylinders:\n");
    for (int i = 0; i < scene->cylinder_count; i++) {
        t_cylinder *cylinder = &scene->cylinders[i];
        printf("  Cylinder %d: center = %f,%f,%f, axis = %f,%f,%f, diameter = %f, height = %f, color = %d,%d,%d\n", i+1,
               cylinder->center.x, cylinder->center.y, cylinder->center.z,
               cylinder->axis.x, cylinder->axis.y, cylinder->axis.z,
               cylinder->diameter, cylinder->height, 
               cylinder->color.red, cylinder->color.green, cylinder->color.blue);
    }
}


int	main(int argc, char **argv)
{
	t_data		data;
	int			fd;
	t_data		*scene;

	if (argc != 2)
	{
		printf(RED"Error: input number has to be one\n"RESET);
		return (1);
	}
	fd = open_rt(argc, argv);
	if (fd == -1)
		return (1);
	
	//data = parse_rt(fd);
	// if (data == NULL)
	//  	free_data with some Error\n message and exit;
	//init_data(&data); or in parse_rt if we can set up everything
	scene = (t_data *)malloc(sizeof(t_data));
	if (scene == NULL)
	{
		printf(RED"Error: Memory allocation failed for scene\n"RESET);
		close(fd);
		return (1);
	}
	initialize_scene(scene);
	if (parse_scene(scene, fd) == EXIT_FAILURE)
	{
		close(fd);
		return (EXIT_FAILURE);
	}
	close(fd);
	print_ambient(&scene->ambient);
    print_camera(&scene->camera);
    print_light(&scene->light);
    print_spheres(scene);
    print_planes(scene);
    print_cylinders(scene);
	init_mlx(scene);
	free_scene(&scene);
	//free(scene);
	//PUT THIS IN A FUNCTION
	// img->mlx_ptr = mlx_init();
	// if (!img->mlx_ptr)
	// 	print_error(1, img);
	// img->img = mlx_new_image(img->mlx_ptr, PIXEL, PIXEL);
	// if (!img->img)
	// 	print_error(3, img);
	// img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
	// 			&img->line_length, &img->endian);
	// if (!img->addr)
	// 	print_error(4, img);
	// setup_image(img);
	// ft_hooks(img);
	// or do this data->img = &img;//REVERSED, CONNECT DATA TO IMAGE
	// make the scene
}
