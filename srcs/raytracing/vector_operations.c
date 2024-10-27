/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_calculation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngtina1999 <ngtina1999@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:28:19 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/10/27 20:02:34 by ngtina1999       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

float vector_length(t_vec3d v)
{
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

t_vec3d	add_vector(t_vec3d v1, t_vec3d v2)
{
	return ((t_vec3d){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z});
}

t_vec3d	subtract_vector(t_vec3d v1, t_vec3d v2)
{
	return ((t_vec3d){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z});
}

t_vec3d	scale_vector(t_vec3d v, float scale)
{
	return ((t_vec3d){v.x * scale, v.y * scale, v.z * scale});
}
