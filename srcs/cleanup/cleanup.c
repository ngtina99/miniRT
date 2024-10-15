#include "../../includes/minirt.h"

void free_scene(t_data **scene) 
{
    if ((*scene)->spheres) {
        free((*scene)->spheres);
    }
    if ((*scene)->planes) {
        free((*scene)->planes);
    }
    if ((*scene)->cylinders) {
        free((*scene)->cylinders);
    }
    free(*scene);
    *scene = NULL;
}
