/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:04:35 by axbrisse          #+#    #+#             */
/*   Updated: 2022/12/22 03:38:27 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h> // TODO

void	pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	dst = data->addr + data->line_length * y + data->bits_per_pixel / 8 * x;
	*(unsigned int *)dst = color;
}

int lerp_component(int c0, int c1, int dist, int dist_max)
{
	return ((c0 * dist + c1 * (dist_max - dist)) / dist_max);
}

int	lerp_color(int c0, int c1, int dist, int dist_max)
{
	return (lerp_component(c0 >> 16, c1 >> 16, dist, dist_max) << 16
		| lerp_component(c0 >> 8 & 255, c1 >> 8 & 255, dist, dist_max) << 8
		| lerp_component(c0 & 255, c1 & 255, dist, dist_max));
}

void	line(t_data *data, int x0, int y0, int c0, int x1, int y1, int c1)
{
    int dx = abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;
    int error = dx + dy;
    
    while (true)
	{
        pixel_put(data, x0, y0, lerp_color(c0, c1, abs(x0-x1) + abs(y0-y1), dx-dy));
        if (x0 == x1 && y0 == y1) return ;
        int e2 = 2 * error;
        if (e2 >= dy)
		{
            if (x0 == x1) return ;
            error += dy;
            x0 += sx;
		}
        if (e2 <= dx)
		{
            if (y0 == y1) return ;
            error += dx;
            y0 += sy;
		}
    }
}

int	render_frame(t_data *data)
{
	const double start_x = WINDOW_WIDTH / 2.0;
	const double start_y = 100.0;
	const double dx = cos(M_PI / 6) * 20;
	const double dy = sin(M_PI / 6) * 20;
	int	**xs;
	int	**ys;

	if (!initialize_grid(&xs, data->map.width, data->map.height) || !initialize_grid(&ys, data->map.width, data->map.height))
		close_window(data);
	for (size_t y = 0; y < data->map.height; ++y)
	{
		for (size_t x = 0; x < data->map.width; ++x)
		{
			double xx = start_x + dx * (int)(x - y);
			double yy = start_y + dy * (x + y) - data->map.zs[y][x] * 2;
			xs[y][x] = (int)xx;
			ys[y][x] = (int)yy;
		}
	}
	for (size_t y = 0; y < data->map.height; ++y)
	{
		for (size_t x = 0; x < data->map.width; ++x)
		{
			if (x+1 != data->map.width)
				line(data, xs[y][x], ys[y][x], data->map.colors[y][x], xs[y][x+1], ys[y][x+1], data->map.colors[y][x+1]);
			if (y+1 != data->map.height)
				line(data, xs[y][x], ys[y][x], data->map.colors[y][x], xs[y+1][x], ys[y+1][x], data->map.colors[y+1][x]);
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	initialize_map(&data.map);
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
	render_frame(&data); // mlx_loop_hook(data.mlx, &render_frame, &data);
	mlx_loop(data.mlx);
	return (EXIT_SUCCESS);
}
