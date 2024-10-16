/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:49:19 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/10/15 13:38:21 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	open_rt(int argc, char **argv)
{
	char	*file_name;
	int		fd;

	file_name = argv[1];
	char *full_path = malloc((PATH_LEN) + ft_strlen(file_name) + 1);
	if (!full_path)
		return (-1);
	ft_strcpy(full_path, "./scenes/");
	ft_strcat(full_path, argv[1]);
	fd = open(full_path, O_RDONLY);
	if (fd == -1)
	{
		printf(RED"Error: input not an existing .rt file\n"RESET);
		return (-1);
	}
	free(full_path);
	return (fd);
}
