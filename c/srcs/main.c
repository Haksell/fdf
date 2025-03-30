/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:04:35 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/07 15:53:57 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int main(int argc, char** argv) {
    char* filename;
    t_data data;

    ft_bzero(&data, sizeof(data));
    data.projection = ISOMETRIC;
    data.should_rerender = true;
    filename = argv[1];
    if (argc != 2 || !ft_endswith(filename, ".fdf")) return (complain(&data, "Usage: ./fdf *.fdf"));
    if (!parse_map(filename, &data.map)) return (complain(&data, "Failed to parse the map"));
    data.colors = init_vertices(WINDOW_WIDTH, WINDOW_HEIGHT);
    if (data.colors == NULL) return (complain(&data, "Failed to initialize colors"));
    if (!init_minilibx(&data, filename)) return (complain(&data, "Failed to initialize mlx"));
    init_params(&data);
    mlx_hook(data.win, ON_DESTROY, NO_EVENT_MASK, close_window, &data);
    mlx_hook(data.win, ON_KEY_DOWN, KEY_PRESS_MASK, handle_key_down, &data);
    mlx_hook(data.win, ON_MOUSE_DOWN, B_PRESS_MASK, handle_mouse_down, &data);
    mlx_hook(data.win, ON_MOUSE_UP, B_RELEASE_MASK, handle_mouse_up, &data);
    mlx_loop_hook(data.mlx, &render_frame, &data);
    mlx_loop(data.mlx);
    return (EXIT_SUCCESS);
}
