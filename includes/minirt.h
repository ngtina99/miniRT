#ifndef FRACTOL_H
# define FRACTOL_H

# define PIXEL 600
# define ESCAPE_VALUE 4

typedef struct s_position
{
	double	a;
	double	b;
	double	x;
	double	y;
}				t_position;	

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

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>

typedef struct s_data 
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	double	arg2;
	double	arg3;
	int		set;
	int		scheme;
	double	colorrange;
	int		red;
	int		green;
	int		blue;
	double	m_x;
	double	m_y;
	double	zoom;
	double	offset_x;
	double	offset_y;
	int		iter;
}				t_data;

#endif