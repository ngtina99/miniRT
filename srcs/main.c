/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:49:19 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/10/25 08:51:08 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	main(int argc, char **argv)
{
	t_data		data;
	int			fd;
	t_data		*scene;

	if (argc != 2)
	{
		printf(RED "Error: Please put a valid .rt file path as an argument\n" RESET);
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
	/* print_ambient(&scene->ambient);
    print_camera(&scene->camera);
    print_light(&scene->light);
    print_spheres(scene);
    print_planes(scene);
    print_cylinders(scene); */
	init_mlx(scene);
	free_scene(&scene);
}
