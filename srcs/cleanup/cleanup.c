/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngtina1999 <ngtina1999@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 01:23:56 by ngtina1999        #+#    #+#             */
/*   Updated: 2024/11/09 01:24:39 by ngtina1999       ###   ########.fr       */
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
	free(*scene);
	*scene = NULL;
}
