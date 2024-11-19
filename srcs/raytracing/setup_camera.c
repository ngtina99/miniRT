/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:28:19 by thuy-ngu          #+#    #+#             */
/*   Updated: 2024/11/19 16:30:40 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_vec3d	setup_camera(t_data *data, int x, int y)
{
	t_vec3d		result_dir;
	t_setup_cam	cam;

	cam.forward = normalize(data->camera.orientation);
	cam.world_up = (t_vec3d){0.0f, 1.0f, 0.0f};
	cam.right = normalize(cross_product(cam.forward, cam.world_up));
	cam.up = normalize(cross_product(cam.right, cam.forward));
	cam.aspect_ratio = (float)WIDTH / HEIGHT;
	cam.scale = tan(data->camera.fov * 0.5 * M_PI / 180.0f);
	cam.px = (2.0f * x / WIDTH - 1.0f) * cam.aspect_ratio * cam.scale;
	cam.py = (1.0f - 2.0f * y / HEIGHT) * cam.scale;
	result_dir.x = cam.forward.x + cam.px * cam.right.x + cam.py * cam.up.x;
	result_dir.y = cam.forward.y + cam.px * cam.right.y + cam.py * cam.up.y;
	result_dir.z = cam.forward.z + cam.px * cam.right.z + cam.py * cam.up.z;
	return (normalize(result_dir));
}
