#ifndef MINIRT_H
# define MINIRT_H

# include "parsing.h"

# include "../libs/libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <stdbool.h>

# ifdef __APPLE__
#  include "../libs/minilibx-mac/mlx.h"
#  define IS_APPLE 1
#  define ESC 53
#  define UP 126
#  define DOWN 125
#  define LEFT 123
#  define RIGHT 124
# else
#  include "../libs/minilibx-linux/mlx.h"
#  define IS_APPLE 0
#  define ESC 65307
#  define UP 65362
#  define DOWN 65364
#  define LEFT 65361
#  define RIGHT 65363
# endif


# define WIDTH 1200
# define HEIGHT 1200

#define PATH_LEN 9
//COLORCODES
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define BLACK "\033[30m"

//KEYCODES
# define SPACE 32
# define ONE 49
# define TWO 50
# define THREE 51
# define FOUR 52
# define FIVE 53
# define SIX 54
# define SEVEN 55
# define Z 122
# define X 120
# define W 119
# define S 115
# define A 97
# define D 100
# define R 114
# define G 103
# define B 98
# define I 105
# define O 111
// # define ESC 65307
// # define UP 65364
// # define DOWN 65362
// # define RIGHT 65363
// # define LEFT 65361

//EVENTCODES
enum	key_codes
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

# define EPSILON 1e-4

enum	object_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	CY_TOP,
	CY_BOTTOM
};

typedef struct s_data t_data;

typedef struct	s_graphic {
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_data	*data;
}				t_graphic;

typedef struct s_data {
    t_ambient ambient;      // Single ambient light
    t_camera camera;             // Single camera
    t_light light;               // Single light
    
    t_sphere *spheres;           // Dynamic array of spheres
    int sphere_count;          // Number of spheres
	int	sphere_capacity;

    t_plane *planes;             // Dynamic array of planes
    int plane_count;           // Number of planes
	int	plane_capacity;

    t_cylinder *cylinders;       // Dynamic array of cylinders
    int cylinder_count;        // Number of cylinders
	int	cylinder_capacity;

	// TODO: we probably won't need this at all
	int	red;//init to 0
	int	green;
	int	blue;

	t_graphic	*img;

} t_data;

typedef struct s_ray
{
    t_vec3d origin;    // Starting point of the ray (camera position)
    t_vec3d direction; // Direction the ray is traveling
}   t_ray;

typedef struct s_object_hit
{
	t_vec3d hit_point;
	int object_type;
	int object_color;
	int	object_index;
} t_object_hit;

typedef struct s_discr_util
{
	float	a;
	float	b;
	float	c;
	float	discriminant;
} t_discr_util;

typedef struct s_cyl_intersection_util
{
	t_vec3d	cylinder_axis;
	t_vec3d	ray_dir_perp;
	t_vec3d	oc_perp;
	float	ray_dir_parallel;
	float	oc_parallel;
}			t_cyl_intersection_util;

int		open_rt(int argc, char **argv);
void	init_mlx(t_data *data);
int 	convert_rgb_to_int(t__color_rgb color);
void	my_mlx_pixel_put(t_graphic *data, int x, int y, int color);
void	init_scene_img(t_data *data);
void	initialize_scene(t_data *scene);
int		parse_scene(t_data *scene, int fd);
void	free_scene(t_data **scene);
t_vec3d add_vector(t_vec3d v1, t_vec3d v2);
t_vec3d subtract_vector(t_vec3d v1, t_vec3d v2);
t_vec3d	scale_vector(t_vec3d v, float scale);
float vector_length(t_vec3d v);
t_vec3d	normalize(t_vec3d v);
t_vec3d	cross_product(t_vec3d v1, t_vec3d v2);
float	dot_product(t_vec3d v1, t_vec3d v2);
void	ray_trace(t_data *data, int x, int y);
float	calculate_distance(t_vec3d point1, t_vec3d point2);
bool	ray_sphere_intersection(t_sphere sphere, t_vec3d origin, t_vec3d direction, t_vec3d *hit_point);
bool 	ray_plane_intersection(t_plane plane, t_vec3d origin, t_vec3d direction, t_vec3d *hit_point);
bool	ray_cylinder_intersection(t_cylinder cylinder, t_vec3d ray_origin, t_vec3d ray_direction, t_vec3d *hit_point);
bool	ray_cylinder_top(t_cylinder cylinder, t_vec3d ray_origin, t_vec3d ray_direction, t_vec3d *hit_point);
bool	ray_cylinder_bottom(t_cylinder cylinder, t_vec3d ray_origin, t_vec3d ray_direction, t_vec3d *hit_point);
int		ft_mousehooks(int button, int x, int y, t_data *img);
int		ft_keyhooks(int keycode, t_data *img);
t_vec3d	setup_camera(t_data *data, int x, int y);
float	calculate_nearest_inters_p(float a, float b, float discriminant);

# ifdef __APPLE__
void		mlx_destroy_display(void *mlx_ptr);
# endif

#endif