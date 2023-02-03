/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:04:35 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/03 05:42:33 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

bool	dup_vertices(t_map *map, t_vertex ***copy)
{
	int	x;
	int	y;

	if (!init_grid((void ***)copy, map->width, map->height, sizeof(t_vertex)))
		return (false);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			(*copy)[y][x] = map->vertices[y][x];
			++x;
		}
		++y;
	}
	return (true);
}

void	rotate(t_data *data, t_vertex **vertices)
{
	int		i;
	int		j;
	double	dist;
	double	angle;

	i = 0;
	while (i < data->map.height)
	{
		j = 0;
		while (j < data->map.width)
		{
			dist = hypot(xs[i][j], ys[i][j]);
			angle = atan2(ys[i][j], xs[i][j]) + data->params.rx;
			xs[i][j] = dist * cos(angle);
			ys[i][j] = dist * sin(angle);
			++j;
		}
		++i;
	}
}

void	scale(t_data *data, t_vertex **vertices)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map.height)
	{
		j = 0;
		while (j < data->map.width)
		{
			vertices[i][j].x *= data->params.scale;
			vertices[i][j].y *= data->params.scale;
			++j;
		}
		++i;
	}
}

void	translate(t_data *data, t_vertex **vertices)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			vertices[y][x].x += data->params.tx;
			vertices[y][x].y += data->params.ty;
			++x;
		}
		++y;
	}
}

int render_frame(t_data *data)
{
	t_vertex **copy;

	if (!data->is_modified)
		return (EXIT_SUCCESS);
	black_background(data);
	if (!dup_vertices(&data->map, &copy))
		close_window(data);
	rotate(data, copy);
	scale(data, copy);
	translate(data, copy);
	for (int y = 0; y < data->map.height; ++y)
	{
		for (int x = 0; x < data->map.width; ++x)
		{
			if (x + 1 < data->map.width)
				line(data, (int)copy[y][x].x, (int)copy[y][x].y, copy[y][x].color, (int)copy[y][x + 1].x, (int)copy[y][x + 1].y, copy[y][x + 1].color);
			if (y + 1 < data->map.height)
				line(data, (int)copy[y][x].x, (int)copy[y][x].y, copy[y][x].color, (int)copy[y + 1][x].x, (int)copy[y + 1][x].y, copy[y + 1][x].color);
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	data->is_modified = false;
	return (EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
	t_data data;

	if (argc != 2 || !parse_map(argv[1], &data.map))
	{
		ft_putendl_fd("Usage: ./fdf *.fdf", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	init_params(&data);
	data.is_modified = true;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, argv[0]);
	data.img = mlx_new_image(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	mlx_hook(data.win, ON_DESTROY, NO_EVENT_MASK, close_window, &data);
	mlx_hook(data.win, ON_KEY_DOWN, KEY_PRESS_MASK, handle_key_down, &data);
	mlx_hook(data.win, ON_MOUSE_DOWN, BUTTON_PRESS_MASK, handle_mouse_down, &data);
	mlx_loop_hook(data.mlx, &render_frame, &data);
	mlx_loop(data.mlx);
	return (EXIT_SUCCESS);
}
