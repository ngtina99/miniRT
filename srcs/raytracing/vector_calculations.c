/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_calculations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngtina1999 <ngtina1999@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 20:07:04 by ngtina1999        #+#    #+#             */
/*   Updated: 2024/10/27 20:16:21 by ngtina1999       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Function to calculate the Euclidean distance between two points in 3D space
// Function to calculate the dot product of two 3D vectors
//measure of similarities
float	dot_product(t_vec3d v1, t_vec3d v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

// Function to calculate the cross product of two 3D vectors
//measure of differences
// The cross product is not commutative, so → u × → v ≠ → v × → u . If we are given 2 vectors: → u = { u 1 , u 2 , u 3 } and → v = { v 1 , v 2 , v 3 } , 
//  the formula is: → u × → v = { u 2 ⋅ v 3 − u 3 ⋅ v 2 , u 3 ⋅ v 1 − u 1 ⋅ v 3 , u 1 ⋅ v 2 − u 2 ⋅ v 1 }
t_vec3d	cross_product(t_vec3d v1, t_vec3d v2)
{
	t_vec3d	result;

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return (result);
}

// Function to normalize the direction vector
// A unit vector has a length (magnitude) of 1, meaning it represents only the direction without an influence from its original length
// This is crucial when you only need to know where the vector is pointing, not how far along it extends, such as in ray tracing or lighting calculations
t_vec3d	normalize(t_vec3d v)
{
	float	magnitude;

	magnitude = vector_length(v);
	if (magnitude == 0.0f) //TODO question in useful.txt, I think we should return only 0.0 for all
		return (t_vec3d){0.0f, 0.0f, -1.0f};
	v.x /= magnitude;
	v.y /= magnitude;
	v.z /= magnitude;
	return (v);
}

float	calculate_distance(t_vec3d point1, t_vec3d point2)
{
	t_vec3d v_distance; 
	v_distance = subtract_vector(point1, point2);
	return (vector_length(v_distance));
}
