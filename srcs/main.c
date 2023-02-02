/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:04:35 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/03 00:30:45 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h> // TODO

static unsigned int get_max(unsigned int n1, unsigned int n2)
{
	if (n1 > n2)
		return (n1);
	else
		return (n2);
}

int render_frame(t_data *data)
{
	const double start_x = WINDOW_WIDTH / 2.0;
	const double start_y = WINDOW_HEIGHT - 50.0;
	const double cell_size = start_x / get_max(data->map.width, data->map.height);
	const double dx = cos(M_PI / 6) * cell_size;
	const double dy = sin(M_PI / 6) * cell_size;
	int **xs;
	int **ys;

	if (!initialize_grid((void ***)&xs, data->map.width, data->map.height, sizeof(int))
		|| !initialize_grid((void ***)&ys, data->map.width, data->map.height, sizeof(int)))
		close_window(data);
	for (int y = 0; y < data->map.height; ++y)
	{
		for (int x = 0; x < data->map.width; ++x)
		{
			int ty = data->map.height - y - 1;
			double xx = start_x + dx * (x - ty);
			double yy = start_y - dy * (x + ty) - data->params.z_factor * data->map.zs[y][x] / data->params.z_factor;
			xs[y][x] = (int)xx;
			ys[y][x] = (int)yy;
		}
	}
	for (int y = 0; y < data->map.height; ++y)
	{
		for (int x = 0; x < data->map.width; ++x)
		{
			if (x + 1 != data->map.width)
				line(data, xs[y][x], ys[y][x], data->map.colors[y][x], xs[y][x + 1], ys[y][x + 1], data->map.colors[y][x + 1]);
			if (y + 1 != data->map.height)
				line(data, xs[y][x], ys[y][x], data->map.colors[y][x], xs[y + 1][x], ys[y + 1][x], data->map.colors[y + 1][x]);
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

int main(int argc, char **argv)
{
	t_data data;

	initialize_map(&data.map);
	if (argc != 2 || !parse_map(argv[1], &data.map))
	{
		ft_putendl_fd("Usage: ./fdf *.fdf", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	data.params.z_factor = 42.0;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, argv[0]);
	data.img = mlx_new_image(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	mlx_hook(data.win, ON_DESTROY, NO_EVENT_MASK, close_window, &data);
	mlx_hook(data.win, ON_KEY_DOWN, KEY_PRESS_MASK, handle_key_down, &data);
	mlx_loop_hook(data.mlx, &render_frame, &data);
	mlx_loop(data.mlx);
	return (EXIT_SUCCESS);
}
