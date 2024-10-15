#ifndef PARSING_H
# define PARSING_H

# define INITIAL_CAPACITY 10 

typedef struct s_ambient {
    float ratio;       // Ambient lighting ratio [0.0, 1.0]
    int color[3];      // RGB color [0-255]
} t_ambient;

typedef struct s_camera {
    float position[3];  // Camera position (x, y, z)
    float orientation[3];  // Normalized orientation vector (x, y, z) [-1, 1]
    int fov;            // Field of view (FOV) [0, 180]
} t_camera;

typedef struct s_light{
    float position[3];  // Light position (x, y, z)
    float brightness;   // Brightness ratio [0.0, 1.0]
    int color[3];       // RGB color [0-255]
} t_light;

typedef struct s_sphere{
    float center[3];    // Sphere center (x, y, z)
    float diameter;     // Sphere diameter
    int color[3];       // RGB color [0-255]
} t_sphere;

typedef struct s_cylinder {
    float center[3];    // Center of the cylinder base (x, y, z)
    float axis[3];      // Normalized axis direction (x, y, z) [-1, 1]
    float diameter;     // Cylinder diameter
    float height;       // Cylinder height
    int color[3];       // RGB color [0-255]
} t_cylinder;

typedef struct s_plane {
    float point[3];     // A point on the plane (x, y, z)
    float normal[3];    // Normal vector of the plane (x, y, z) [-1, 1]
    int color[3];       // RGB color [0-255]
} t_plane;

#endif