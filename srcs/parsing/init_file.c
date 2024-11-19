/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:49:19 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/11/19 16:34:36 by yioffe           ###   ########.fr       */
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

// int	open_rt(int argc, char **argv)
// {
// 	char	*file_name;
// 	int		fd;
// 	char	*full_path;

// 	file_name = argv[1];
// 	full_path = malloc((PATH_LEN) + ft_strlen(file_name) + 1);
// 	if (!full_path)
// 			return (-1);
// 	ft_strcpy(full_path, "./scenes/");
// 	ft_strcat(full_path, argv[1]);
// 	fd = open(full_path, O_RDONLY);
// 	if (fd == -1)
// 	{
// 		if()
// 			break;
// 		else
// 		{
// 			free(full_path);
// 			printf(RED"Error: input not an existing .rt file\n"RESET);
// 			return (-1);
// 		}
// 	}
// 	free(full_path);
// 	return (fd);
// }
