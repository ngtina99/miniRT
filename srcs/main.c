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

static void	error_message(int fd)
{
	ft_putstr_fd("Error\nMemory allocation failed for scene\n", 
	STDERR_FILENO);
	close(fd);
}

int	main(int argc, char **argv)
{
	int			fd;
	t_data		*scene;

	if (argc != 2)
		return (ft_putstr_fd("Error\n Provide .rt path", STDERR_FILENO),
			EXIT_FAILURE);
	fd = open_rt(argv);
	if (fd == -1)
		return (EXIT_FAILURE);
	scene = (t_data *)malloc(sizeof(t_data));
	if (scene == NULL)
		return(error_message(fd), EXIT_FAILURE);
	initialize_scene(scene);
	if (parse_scene(scene, fd) == EXIT_FAILURE)
	{
		close(fd);
		free_scene(&scene);
		ft_putstr_fd("Not valid .rt\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	close(fd);
	init_mlx(scene);
	free_scene(&scene);
	return (EXIT_SUCCESS);
}
