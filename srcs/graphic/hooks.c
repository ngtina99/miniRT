/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngtina1999 <ngtina1999@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:19:53 by ngtina1999        #+#    #+#             */
/*   Updated: 2024/10/29 18:21:38 by ngtina1999       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	ft_mousehooks(int button, int x, int y, t_data *img)
{
	img->offset_x = (x - (PIXEL / 2)) * 0.1;
	img->offset_y = (y - (PIXEL / 2)) * 0.1;
	if (button == ON_MOUSEDOWN)
	{
		img->m_x = img->m_x * 1.1 + img->offset_x;
		img->m_y = img->m_y * 1.1 + img->offset_y;
		img->zoom *= 1.1;
	}
	if (button == ON_MOUSEUP)
	{
		img->m_x = img->m_x / 1.1 + img->offset_x;
		img->m_y = img->m_y / 1.1 + img->offset_y;
		img->zoom /= 1.1;
	}
	setup_image(img);
	return (0);
}

int	ft_keyhooks(int keycode, t_data *img)
{
	if (keycode == UP)
		img->m_y += 10;
	else if (keycode == DOWN)
		img->m_y -= 10;
	else if (keycode == RIGHT)
		img->m_x += 10;
	else if (keycode == LEFT)
		img->m_x -= 10;
	setup_image(img);
}