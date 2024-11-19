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

int	apply_shading(int base_color, float intensity)
{
	int	red;
	int	green;
	int	blue;

	red = ((base_color >> 16) & 0xFF) * intensity;
	green = ((base_color >> 8) & 0xFF) * intensity;
	blue = (base_color & 0xFF) * intensity;
	return ((red << 16) | (green << 8) | (blue));
}

bool	is_in_shadow(t_data *data, t_vec3d hit_point, t_vec3d light_dir)
{
	t_object_hit	shadow_hit;

	return (find_closest_object(data, hit_point, light_dir, &shadow_hit)
		&& (calculate_distance(hit_point, shadow_hit.hit_point) + 0.001f)
		< calculate_distance(hit_point, data->light.position));
}
