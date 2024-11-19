/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_paraboloid.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:06:24 by yioffe            #+#    #+#             */
/*   Updated: 2024/11/19 17:06:34 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	parse_paraboloid(t_data *scene, char *line)
{
	t_paraboloid		paraboloid;
	t_add_form_params	params;

	line += 2;
	parse_vector(&line, &paraboloid.vertex); // Parse the vertex
	parse_vector(&line, &paraboloid.axis);   // Parse the axis (normalized)
	paraboloid.curvature = parse_float(&line); // Parse curvature factor
	paraboloid.height = parse_float(&line); // Parse height
	parse_rgb(&line, &paraboloid.color);    // Parse the color
	params.array = (void **)&scene->paraboloids;
	params.count = &scene->paraboloid_count;
	params.capacity = &scene->paraboloid_capacity;
	params.form_size = sizeof(t_paraboloid);
	return (add_form(&params, &paraboloid));
}

