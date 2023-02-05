/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:04:35 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/05 04:46:27 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int render_frame(t_data *data)
{
	t_vertex **vertices;

	if (!data->should_rerender)
		return (EXIT_SUCCESS);
	vertices = copy_vertices(data);
	if (vertices == NULL)
		close_window(data);
	black_background(data);
	transform_vertices(data, vertices);
	put_lines(data, vertices);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	data->should_rerender = false;
	ft_free_double_pointer((void **)vertices, data->map.height);
	return (EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
	t_data data;

	if (argc != 2 || !ft_endswith(argv[1], ".fdf"))
		return (complain("Usage: ./fdf *.fdf"));
	if (!parse_map(argv[1], &data.map))
		return (complain("Failed to parse the map"));
	if (!init_minilibx(&data, argv[0]))
		return (complain("Failed to initialize mlx"));
	init_params(&data);
	data.should_rerender = true;
	mlx_hook(data.win, ON_DESTROY, NO_EVENT_MASK, close_window, &data);
	mlx_hook(data.win, ON_KEY_DOWN, KEY_PRESS_MASK, handle_key_down, &data);
	mlx_hook(data.win, ON_MOUSE_DOWN, BUTTON_PRESS_MASK, handle_mouse_down, &data);
	mlx_loop_hook(data.mlx, &render_frame, &data);
	mlx_loop(data.mlx);
	return (EXIT_SUCCESS);
}
