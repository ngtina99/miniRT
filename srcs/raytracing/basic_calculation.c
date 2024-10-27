/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_calculation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngtina1999 <ngtina1999@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:28:19 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/10/27 15:58:40 by ngtina1999       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

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

// Function to calculate the dot product of two 3D vectors
//measure of similarities
float	dot_product(t_vec3d v1, t_vec3d v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

// Function to calculate the cross product of two 3D vectors
//measure of differences
t_vec3d	cross_product(t_vec3d v1, t_vec3d v2)
{
	t_vec3d	result;

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return (result);
}
