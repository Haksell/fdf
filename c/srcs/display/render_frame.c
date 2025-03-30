#include "../../includes/fdf.h"

static t_vertex** copy_vertices(t_data* data) {
    t_vertex** copy;
    int x;
    int y;

    copy = init_vertices(data->map.width, data->map.height);
    if (copy == NULL) return (NULL);
    y = 0;
    while (y < data->map.height) {
        x = 0;
        while (x < data->map.width) {
            copy[y][x] = data->map.vertices[y][x];
            copy[y][x].z *= data->params.altitude;
            ++x;
        }
        ++y;
    }
    return (copy);
}

static void reset_background(t_data* data) {
    int x;
    int y;

    y = 0;
    while (y < WINDOW_HEIGHT) {
        x = 0;
        while (x < WINDOW_WIDTH) {
            data->colors[y][x].color = BACKGROUND;
            data->colors[y][x].z = -INFINITY;
            ++x;
        }
        ++y;
    }
}

static void put_colors_to_image(t_data* data) {
    int x;
    int y;

    y = 0;
    while (y < WINDOW_HEIGHT) {
        x = 0;
        while (x < WINDOW_WIDTH) {
            pixel_put(data, x, y, data->colors[y][x].color);
            ++x;
        }
        ++y;
    }
}

int render_frame(t_data* data) {
    t_vertex** vertices;

    if (!data->should_rerender) return (EXIT_SUCCESS);
    vertices = copy_vertices(data);
    if (vertices == NULL) close_window(data);
    reset_background(data);
    transform_vertices(data, vertices);
    put_lines(data, vertices);
    put_colors_to_image(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    data->should_rerender = false;
    ft_free_double_pointer((void***)&vertices, data->map.height);
    return (EXIT_SUCCESS);
}
