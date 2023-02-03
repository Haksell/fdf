/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:04:35 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/03 06:42:10 by axbrisse         ###   ########.fr       */
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

void	rotate_vertex(double *d1, double *d2, double rotation)
{
	const double	dist = hypot(*d1, *d2);
	const double	angle = atan2(*d2, *d1) + rotation;

	*d1 = dist * cos(angle);
	*d2 = dist * sin(angle);
}

void	rotate(t_data *data, t_vertex **copy)
{
	int		x;
	int		y;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			rotate_vertex(&copy[y][x].x, &copy[y][x].y, data->params.rz);
			rotate_vertex(&copy[y][x].y, &copy[y][x].z, data->params.rx);
			rotate_vertex(&copy[y][x].z, &copy[y][x].x, data->params.ry);
			++x;
		}
		++y;
	}
}

void	scale(t_data *data, t_vertex **copy)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			copy[y][x].x *= data->params.scale;
			copy[y][x].y *= data->params.scale;
			copy[y][x].z *= data->params.scale;
			++x;
		}
		++y;
	}
}

void	project(t_data *data, t_vertex **copy)
{
	// TODO switch on params.projection
	const double dx = cos(M_PI / 6);
	const double dy = sin(M_PI / 6);
	int	x;
	int	y;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			int tmpx = copy[y][x].x;
			int tmpy = copy[y][x].y;
			copy[y][x].x = dx * (tmpx - data->map.height + tmpy + 1);
			copy[y][x].y = dy * -(tmpx + data->map.height - tmpy - 1);
			++x;
		}
		++y;
	}
}

void	translate(t_data *data, t_vertex **copy)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			copy[y][x].x += data->params.tx;
			copy[y][x].y += data->params.ty;
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
	project(data, copy); // TODO switch on params.projection
	translate(data, copy);
	put_lines(data, copy);
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
