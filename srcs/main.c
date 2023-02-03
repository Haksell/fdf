/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:04:35 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/03 02:43:05 by axbrisse         ###   ########.fr       */
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

void	translate(t_data *data, double **points, double translation)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map.height)
	{
		j = 0;
		while (j < data->map.width)
		{
			// printf("before i=%d j=%d\n", i, j);
			points[i][j] += translation;
			// printf("after  i=%d j=%d\n", i, j);
			++j;
		}
		++i;
	}
}

int render_frame(t_data *data)
{
	const double start_x = WINDOW_WIDTH / 2.0;
	const double start_y = WINDOW_HEIGHT - 50.0;
	const double cell_size = start_x / get_max(data->map.width, data->map.height);
	const double dx = cos(M_PI / 6) * cell_size;
	const double dy = sin(M_PI / 6) * cell_size;
	// const double middle_x = start_x + dx * (data->map.width - data->map.height) / 2;
	// const double middle_y = start_y - dy * (data->map.width + data->map.height - 2) / 2;
	double **xs;
	double **ys;

	// TODO if (!is_modified)
	black_background(data);
	if (!init_grid((void ***)&xs, data->map.width, data->map.height, sizeof(double))
		|| !init_grid((void ***)&ys, data->map.width, data->map.height, sizeof(double)))
		close_window(data);
	for (int y = 0; y < data->map.height; ++y)
	{
		for (int x = 0; x < data->map.width; ++x)
		{
			xs[y][x] = start_x + dx * (x - data->map.height + y + 1);
			ys[y][x] = start_y - dy * (x + data->map.height - y - 1);
			ys[y][x] -= data->params.z_factor * data->map.zs[y][x];
		}
	}
	// translate(data, xs, -middle_x);
	// translate(data, ys, -middle_y);
	// rotate(data, xs, ys, middle_x, middle_y); // TODO not as args
	// translate(data, xs, middle_x);
	translate(data, ys, 0);
	// ft_printf("translate 1\n");
	// ft_printf("translate 2\n");
	// translate(data, xs, middle_x);
	// ft_printf("translate 3\n");
	// translate(data, ys, middle_y);
	translate(data, xs, data->params.tx);
	translate(data, ys, data->params.ty);
	for (int y = 0; y < data->map.height; ++y)
	{
		for (int x = 0; x < data->map.width; ++x)
		{
			if (x + 1 != data->map.width)
				line(data, (int)xs[y][x], (int)ys[y][x], data->map.colors[y][x], (int)xs[y][x + 1], (int)ys[y][x + 1], data->map.colors[y][x + 1]);
			if (y + 1 != data->map.height)
				line(data, (int)xs[y][x], (int)ys[y][x], data->map.colors[y][x], (int)xs[y + 1][x], (int)ys[y + 1][x], data->map.colors[y + 1][x]);
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	// TODO is_modified = false;
	// TODO free xs, ys
	return (0);
}

int main(int argc, char **argv)
{
	t_data data;

	init_map(&data.map);
	init_params(&data.params);
	if (argc != 2 || !parse_map(argv[1], &data.map))
	{
		ft_putendl_fd("Usage: ./fdf *.fdf", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
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
