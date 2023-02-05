/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:04:35 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/05 01:34:54 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

bool	dup_vertices(t_data *data, t_vertex ***copy)
{
	int	x;
	int	y;

	if (!init_grid((void ***)copy, data->map.width, data->map.height, sizeof(t_vertex)))
		return (false);
	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			(*copy)[y][x] = data->map.vertices[y][x];
			(*copy)[y][x].z *= data->params.altitude;
			++x;
		}
		++y;
	}
	return (true);
}

int render_frame(t_data *data)
{
	t_vertex **copy;

	if (!data->should_rerender)
		return (EXIT_SUCCESS);
	if (!dup_vertices(data, &copy))
		close_window(data);
	black_background(data);
	transform_vertices(data, copy);
	put_lines(data, copy);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	data->should_rerender = false;
	return (EXIT_SUCCESS);
}

int	complain(char *error_message)
{
	ft_putendl_fd(error_message, STDERR_FILENO);
	return (EXIT_FAILURE);
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
