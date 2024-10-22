/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_calculation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thuy-ngu <thuy-ngu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:28:19 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/10/17 17:28:19 by thuy-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// 1. Sub-problem (Points in 3D Space)
// Requirement: to represent vectors

// Create a 3D vector struct that support following operations:

// Vector Addition
// Vector Subtraction
// Vector Magnitude
// Dot Product
// Vector Normalization
// Vector Multiplication (Multiplying a Vector by a scalar)

int	vector_rendering(t_data *data)
{
	int color_code;

	(void)data;

			// data->red = 0;//just for test
			// data->green = 0;//just for test
			// data->blue = 255;//just for test
	
	color_code = (data->red << 16) | (data->green << 8) | data->blue;
	return(color_code);
}
