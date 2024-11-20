/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:49:19 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/11/20 13:22:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	open_rt(int argc, char **argv)
{
	char	*file_name;
	int		fd;

	file_name = argv[1];
	if (ft_strlen(file_name) < 3
		|| ft_strcmp(file_name + ft_strlen(file_name) - 3, ".rt") != 0)
	{
		printf(RED "Error: The file doesn't have a .rt extension\n" RESET);
		return (-1);
	}
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		printf(RED "Error: input is not an existing .rt \
			file path or the file can't be opened\n" RESET);
		return (-1);
	}
	return (fd);
}
