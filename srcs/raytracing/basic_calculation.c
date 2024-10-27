/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_calculation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngtina1999 <ngtina1999@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:28:19 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/10/27 15:31:07 by ngtina1999       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_vec3d add_vector(t_vec3d v1, t_vec3d v2)
{
	t_vec3d	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}

t_vec3d subtract_vector(t_vec3d v1, t_vec3d v2)
{
	t_vec3d	result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}

t_vec3d	scale_vector(t_vec3d v, float scale)
{
	return ((t_vec3d){v.x * scale, v.y * scale, v.z * scale});
}

t_vec3d	normalize(t_vec3d v)
{
	float magnitude;

	magnitude = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	if (magnitude == 0.0f) //TODO mabye it would be better to handle as something else excep bringing back this value
		return (t_vec3d){0.0f, 0.0f, -1.0f};
	v.x /= magnitude;
	v.y /= magnitude;
	v.z /= magnitude;
	return (v);
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

// Function to calculate the dot product of two 3D vectors
//measure of similarities
float	dot_product(t_vec3d v1, t_vec3d v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}