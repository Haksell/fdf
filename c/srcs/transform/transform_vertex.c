#include "../../fdf.h"

void transform_vertex(t_vertex* vertex, t_data* data) {
    static t_transform_func funcs[] = {
        [CABINET] = transform_cabinet,
        [PARALLEL] = transform_parallel,
        [ISOMETRIC] = transform_isometric};

    funcs[data->projection](vertex, data);
}

void inverse_transform_vertex(t_vertex* vertex, t_data* data) {
    static t_transform_func funcs[] = {
        [CABINET] = inverse_transform_cabinet,
        [PARALLEL] = inverse_transform_parallel,
        [ISOMETRIC] = inverse_transform_isometric};

    funcs[data->projection](vertex, data);
}

void transform_vertices(t_data* data, t_vertex** copy) {
    int x;
    int y;

    y = 0;
    while (y < data->map.height) {
        x = 0;
        while (x < data->map.width) {
            transform_vertex(&copy[y][x], data);
            ++x;
        }
        ++y;
    }
}
