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

# include <stdbool.h>

# define INITIAL_CAPACITY 10

typedef struct s_data	t_data;

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

int		parse_scene(t_data *scene, int fd);
int		add_form(t_add_form_params *params, void *new_form);
int		allocate_initial_array(void **array, int *capacity, size_t form_size);
int		resize_array(void **array, int *capacity, int count, size_t form_size);
void	skip_whitespace(char **line);
int		parse_sign(char **line);
void	parse_number(char **line, float *result, float *fraction,
			bool *is_fractional);
float	parse_float(char **line);
int		parse_vector(char **line, t_vec3d *vector);
int		parse_rgb(char **line, t__color_rgb *color);
int		parse_sphere(t_data *scene, char *line);
int		parse_plane(t_data *scene, char *line);
int		parse_cylinder(t_data *scene, char *line);
int		parse_ambient(t_data *scene, char *line);
int		parse_camera(t_data *scene, char *line);
int		parse_light(t_data *scene, char *line);
bool	validator_rgb_end(char *line);
bool	validator_ambient(char *line);
bool	validator_camera(char *line);
bool	validator_light(char *line);
bool	validator_sphere(char *line);
bool	validator_cylinder(char *line);
bool	validator_plane(char *line);
bool	validator_vector3d_with_range(char **line, float min, float max);
bool	validator_float_with_range_inline(char **line, float min, float max);
bool	is_valid_separator(char c);
bool	validator_fov(char **line);

#endif