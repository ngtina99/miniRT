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
		error_message(fd, ARG_ERR);
	fd = open_rt(argc, argv);
	if (fd == -1)
		return (1);
	scene = (t_data *)malloc(sizeof(t_data));
	if (scene == NULL)
		error_message(fd, MALLOC_ERR);
	initialize_scene(scene);
	if (parse_scene(scene, fd) == EXIT_FAILURE)
		error_message(fd, PARSE_ERR);
	close(fd);
	init_mlx(scene);
	free_scene(&scene);
}
