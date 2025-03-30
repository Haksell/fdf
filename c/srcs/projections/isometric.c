#include "../../fdf.h"

static void project_isometric(t_vertex* vertex, t_data* data) {
    const double tmp_x = vertex->x;
    const double tmp_y = vertex->y - data->map.height + 1;

    vertex->x = ISOMETRIC_COS * (tmp_y + tmp_x);
    vertex->y = ISOMETRIC_SIN * (tmp_y - tmp_x) - vertex->z;
}

static void inverse_project_isometric(t_vertex* vertex, t_data* data) {
    static double cs2 = ISOMETRIC_COS * ISOMETRIC_SIN * 2.0;
    const double tmp_x = vertex->x;
    const double tmp_y = vertex->y;

    vertex->x = (ISOMETRIC_SIN * tmp_x - ISOMETRIC_COS * tmp_y) / cs2;
    vertex->y = ((ISOMETRIC_SIN * tmp_x + ISOMETRIC_COS * tmp_y) / cs2 + data->map.height - 1);
}

void transform_isometric(t_vertex* vertex, t_data* data) {
    scale_vertex(vertex, data->params.scale);
    rotate_3d(vertex, data->params.rx, data->params.ry, data->params.rz);
    project_isometric(vertex, data);
    translate_vertex(vertex, data->params.tx, data->params.ty);
}

void inverse_transform_isometric(t_vertex* vertex, t_data* data) {
    translate_vertex(vertex, -data->params.tx, -data->params.ty);
    inverse_project_isometric(vertex, data);
    rotate_2d(&vertex->y, &vertex->z, -data->params.rx);
    rotate_2d(&vertex->z, &vertex->x, -data->params.ry);
    rotate_2d(&vertex->x, &vertex->y, -data->params.rz);
    scale_vertex(vertex, 1.0 / data->params.scale);
}
