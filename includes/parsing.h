#ifndef PARSING_H
# define PARSING_H

# define INITIAL_CAPACITY 10

typedef struct s_vect3d
{
	float x;
	float y;
	float z;
} t_vec3d;

typedef struct s_add_form_params
{
	void **array;
	int *count;
	int *capacity;
	size_t form_size;
} t_add_form_params;

typedef struct s_color_rgb
{
	int red;
	int green;
	int blue;
} t__color_rgb;

typedef struct s_ambient
{
	float ratio;        // Ambient lighting ratio [0.0, 1.0]
	t__color_rgb color; // RGB color [0-255]
} t_ambient;

typedef struct s_camera
{
	t_vec3d position;    // Camera position (x, y, z)
	t_vec3d orientation; // Normalized orientation vector (x, y, z) [-1, 1]
	int fov;             // Field of view (FOV) [0, 180]
} t_camera;

typedef struct s_setup_cam
{
	float aspect_ratio;
	float scale;
	float px;
	float py;
	t_vec3d forward;
	t_vec3d world_up;
	t_vec3d right;
	t_vec3d up;
} t_setup_cam;

typedef struct s_light
{
	t_vec3d position;   // Light position (x, y, z)
	float brightness;   // Brightness ratio [0.0, 1.0]
	t__color_rgb color; // RGB color [0-255]
} t_light;

typedef struct s_sphere
{
	t_vec3d center;     // Sphere center (x, y, z)
	float diameter;     // Sphere diameter
	t__color_rgb color; // RGB color [0-255]
} t_sphere;

typedef struct s_cylinder
{
	t_vec3d center;     // Center of the cylinder base (x, y, z)
	t_vec3d axis;       // Normalized axis direction (x, y, z) [-1, 1]
	float diameter;     // Cylinder diameter
	float height;       // Cylinder height
	t__color_rgb color; // RGB color [0-255]
} t_cylinder;

typedef struct s_plane
{
	t_vec3d point;      // A point on the plane (x, y, z)
	t_vec3d normal;     // Normal vector of the plane (x, y, z) [-1, 1]
	t__color_rgb color; // RGB color [0-255]
} t_plane;

#endif