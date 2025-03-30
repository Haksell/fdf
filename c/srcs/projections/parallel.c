#include "../../fdf.h"

static void project_parallel(t_vertex* vertex, t_data* data) {
    const double tmp_y = vertex->y;

    (void)data;
    vertex->y = -vertex->z;
    vertex->z = -tmp_y;
}

void transform_parallel(t_vertex* vertex, t_data* data) {
    scale_vertex(vertex, data->params.scale);
    rotate_2d(&vertex->x, &vertex->y, data->params.rz);
    project_parallel(vertex, data);
    translate_vertex(vertex, data->params.tx, data->params.ty);
}

void inverse_transform_parallel(t_vertex* vertex, t_data* data) {
    translate_vertex(vertex, -data->params.tx, -data->params.ty);
    project_parallel(vertex, data);
    rotate_2d(&vertex->x, &vertex->y, -data->params.rz);
    scale_vertex(vertex, 1.0 / data->params.scale);
}
