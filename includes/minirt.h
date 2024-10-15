#ifndef MINIRT_H
# define MINIRT_H

# include "parsing.h"

# include "../libs/libft/libft.h"
# include "../libs/minilibx-linux/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>

# define WIDTH 1200
# define HEIGHT 800

# define PIXEL 600//maybe don't need at all

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
# define ESC 65307
# define UP 65364
# define DOWN 65362
# define RIGHT 65363
# define LEFT 65361

//EVENTCODES
enum 
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

// typedef struct s_position// could be usefule maybe later
// {
// 	double	a;
// 	double	b;
// 	double	x;
// 	double	y;
// }				t_position;	

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

	int	red;//init to 0
	int	green;
	int	blue;

	t_graphic	*img;

} t_data;

// typedef struct	s_data {
// //infos from .rt file
// 	int	red;//init to 0
// 	int	green;
// 	int	blue;
// 	t_graphic *img;// I init at init_mlx *search data->img = &img;
// }				t_data;

int		open_rt(int argc, char **argv);
void	init_mlx(t_data *data);
void	my_mlx_pixel_put(t_graphic *data, int x, int y, int color);
void	init_scene_img(t_data *data);
void	initialize_scene(t_data *scene);
int		parse_scene(t_data *scene, int fd);
void	free_scene(t_data **scene);

#endif