#include "../../fdf.h"

int close_window(t_data* data) {
    mlx_destroy_image(data->mlx, data->img);
    mlx_destroy_window(data->mlx, data->win);
    mlx_destroy_display(data->mlx);
    free(data->mlx);
    free_data(data);
    exit(EXIT_SUCCESS);
    return (EXIT_SUCCESS);
}

int complain(t_data* data, char* error_message) {
    free_data(data);
    ft_putendl_fd(error_message, STDERR_FILENO);
    return (EXIT_FAILURE);
}

void ft_free_double_pointer(void*** grid, size_t height) {
    size_t i;

    if (*grid == NULL) return;
    i = 0;
    while (i < height && (*grid)[i] != NULL) {
        ft_free(&(*grid)[i]);
        ++i;
    }
    ft_free((void**)grid);
}

void free_data(t_data* data) {
    ft_free_double_pointer((void***)&data->map.vertices, data->map.height);
    ft_free_double_pointer((void***)&data->colors, WINDOW_HEIGHT);
}
