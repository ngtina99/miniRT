/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 01:23:56 by ngtina1999        #+#    #+#             */
/*   Updated: 2024/11/19 17:07:41 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	free_scene(t_data **scene)
{
	if ((*scene)->spheres)
		free((*scene)->spheres);
	if ((*scene)->planes)
		free((*scene)->planes);
	if ((*scene)->cylinders)
		free((*scene)->cylinders);
	if ((*scene)->paraboloids)
		free((*scene)->paraboloids);
	free(*scene);
	*scene = NULL;
}
