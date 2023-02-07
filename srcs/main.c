/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:04:35 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/07 12:24:48 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	reset_background(t_data *data)
{
	for (int y = 0; y < WINDOW_HEIGHT; ++y) {
		for (int x = 0; x < WINDOW_WIDTH; ++x) {
			data->colors[y][x].color = BACKGROUND;
			data->colors[y][x].z = -INFINITY;
		}	
	}
}

void	put_colors_to_image(t_data *data)
{
	for (int y = 0; y < WINDOW_HEIGHT; ++y)
		for (int x = 0; x < WINDOW_WIDTH; ++x)
			pixel_put(data, x, y, data->colors[y][x].color);
}

int render_frame(t_data *data)
{
	t_vertex **vertices;

	if (!data->should_rerender)
		return (EXIT_SUCCESS);
	vertices = copy_vertices(data);
	if (vertices == NULL)
		close_window(data);
	reset_background(data);
	transform_vertices(data, vertices);
	put_lines(data, vertices);
	put_colors_to_image(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	data->should_rerender = false;
	ft_free_double_pointer((void **)vertices, data->map.height);
	return (EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
	char	*filename;
	t_data	data;

	data.is_bonus = ft_endswith(argv[0], "bonus");
	filename = argv[1];
	data.map.vertices = NULL;
	data.colors = NULL;
	if (argc != 2 || !ft_endswith(filename, ".fdf"))
		return (complain(&data, "Usage: ./fdf *.fdf"));
	if (!parse_map(filename, &data.map))
		return (complain(&data, "Failed to parse the map"));
	data.colors = init_vertices(WINDOW_WIDTH, WINDOW_HEIGHT);
	if (data.colors == NULL)
		return (complain(&data, "Failed to initialize colors"));
	if (!init_minilibx(&data, filename))
		return (complain(&data, "Failed to initialize mlx"));
	data.projection = ISOMETRIC;
	data.should_rerender = true;
	init_params(&data);
	mlx_hook(data.win, ON_DESTROY, NO_EVENT_MASK, close_window, &data);
	mlx_hook(data.win, ON_KEY_DOWN, KEY_PRESS_MASK, handle_key_down, &data);
	mlx_hook(data.win, ON_MOUSE_DOWN, BUTTON_PRESS_MASK, handle_mouse_down, &data);
	mlx_hook(data.win, ON_MOUSE_UP, BUTTON_RELEASE_MASK, handle_mouse_up, &data);
	mlx_loop_hook(data.mlx, &render_frame, &data);
	mlx_loop(data.mlx);
	return (EXIT_SUCCESS);
}
