/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngtina1999 <ngtina1999@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:19:53 by ngtina1999        #+#    #+#             */
/*   Updated: 2024/10/30 13:32:57 by ngtina1999       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// I pushed these 4 new components 
// 	double	m_x;
// 	double	m_y;

// should set up to 0 in the parsing
int	ft_mousehooks(int button, int x, int y, t_data *data)
{
	data->img->offset_x = (x - (WIDTH / 2));
	data->img->offset_y = (y - (HEIGHT / 2));
	if (button == LEFT_CLICK) // it is working for left click 
	{
		//		if(data->img->offset_x) write something to detect where is the point which object exactly
		if(data->img->offset_x)
			return (0) 
		// it should return here the object index to identify so maybe make a new left_click bool and turn trues is it is that object
	}
	return (0);
}

int	ft_keyhooks(int keycode, t_data *data)
{
	// we should connect this to that indexe object
	if (keycode == UP)
		data->img->m_y += 10;
	else if (keycode == DOWN)
		data->img->m_y -= 10;
	else if (keycode == RIGHT)
		data->img->m_x += 10;
	else if (keycode == LEFT)
		data->img->m_x -= 10;
	// I changed every pixel put to this 			my_mlx_pixel_put(data->img, x + data->img->m_x, y + data->img->m_y, 100 + color_code);
	init_scene_img(data);
}