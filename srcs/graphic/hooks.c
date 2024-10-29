/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngtina1999 <ngtina1999@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:19:53 by ngtina1999        #+#    #+#             */
/*   Updated: 2024/10/29 19:22:34 by ngtina1999       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	ft_mousehooks(int button, int x, int y, t_data *data)
{
	data->img->offset_x = (x - (WIDTH / 2));
	data->img->offset_y = (y - (HEIGHT / 2));
	if (button == LEFT_CLICK)
	{
		data->img->m_x = data->img->m_x + data->img->offset_x;
		data->img->m_y = data->img->m_y + data->img->offset_y;
	}
	return (0);
}

int	ft_keyhooks(int keycode, t_data *data)
{
	if (keycode == UP)
		data->img->m_y += 10;
	else if (keycode == DOWN)
		data->img->m_y -= 10;
	else if (keycode == RIGHT)
		data->img->m_x += 10;
	else if (keycode == LEFT)
		data->img->m_x -= 10;
	init_scene_img(data);
}