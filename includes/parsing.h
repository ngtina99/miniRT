/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yioffe <yioffe@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 10:15:33 by yioffe            #+#    #+#             */
/*   Updated: 2024/11/17 10:15:33 by yioffe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define INITIAL_CAPACITY 10

typedef struct s_vect3d
{
	float	x;
	float	y;
	float	z;
}	t_vec3d;

typedef struct s_add_form_params
{
	void	**array;
	int		*count;
	int		*capacity;
	size_t	form_size;
}	t_add_form_params;

typedef struct s_color_rgb
{
	int	red;
	int	green;
	int	blue;
}	t__color_rgb;

typedef struct s_ambient
{
	float			ratio;
	t__color_rgb	color;
}	t_ambient;

typedef struct s_camera
{
	t_vec3d	position;
	t_vec3d	orientation;
	int		fov;
}	t_camera;

typedef struct s_setup_cam
{
	float	aspect_ratio;
	float	scale;
	float	px;
	float	py;
	t_vec3d	forward;
	t_vec3d	world_up;
	t_vec3d	right;
	t_vec3d	up;
}	t_setup_cam;

typedef struct s_light
{
	t_vec3d			position;
	float			brightness;
	t__color_rgb	color;
}	t_light;

typedef struct s_sphere
{
	t_vec3d			center;
	float			diameter;
	t__color_rgb	color;
}	t_sphere;

typedef struct s_cylinder
{
	t_vec3d			center;
	t_vec3d			axis;
	float			diameter;
	float			height;
	t__color_rgb	color;
}	t_cylinder;

typedef struct s_plane
{
	t_vec3d			point;
	t_vec3d			normal;
	t__color_rgb	color;
}	t_plane;

typedef struct s_count
{
	int	a;
	int	c;
	int	l;
}	t_count;

#endif