/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:04:35 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/06 03:16:14 by axbrisse         ###   ########.fr       */
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
	redraw_background(data);
	transform_vertices(data, vertices);
	printf("xa=%.1lf xb=%.1lf\n", vertices[0][0].x, vertices[1][1].x);
	put_lines(data, vertices);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	data->should_rerender = false;
	ft_free_double_pointer((void **)vertices, data->map.height);
	return (EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
	char	*filename;
	t_data	data;

	filename = argv[1];
	if (argc != 2 || !ft_endswith(filename, ".fdf"))
		return (complain("Usage: ./fdf *.fdf"));
	if (!parse_map(filename, &data.map))
		return (complain("Failed to parse the map"));
	if (!init_minilibx(&data, filename))
		return (complain("Failed to initialize mlx"));
	init_params(&data);
	data.should_rerender = true;
	mlx_hook(data.win, ON_DESTROY, NO_EVENT_MASK, close_window, &data);
	mlx_hook(data.win, ON_KEY_DOWN, KEY_PRESS_MASK, handle_key_down, &data);
	mlx_hook(data.win, ON_MOUSE_DOWN, BUTTON_PRESS_MASK, handle_mouse_down, &data);
	mlx_hook(data.win, ON_MOUSE_UP, BUTTON_RELEASE_MASK, handle_mouse_up, &data);
	mlx_loop_hook(data.mlx, &render_frame, &data);
	mlx_loop(data.mlx);
	return (EXIT_SUCCESS);
}
