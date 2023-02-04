/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:04:35 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/04 06:06:06 by axbrisse         ###   ########.fr       */
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
			copy[y][x].y -= copy[y][x].z;
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

	if (!data->should_rerender)
		return (EXIT_SUCCESS);
	if (!dup_vertices(data, &copy))
		close_window(data);
	black_background(data);
	rotate(data, copy);
	scale(data, copy);
	project(data, copy); // TODO switch on params.projection
	translate(data, copy);
	put_lines(data, copy);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	data->should_rerender = false;
	return (EXIT_SUCCESS);
}

bool	initialize_mlx(t_data *data, char *window_title)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		return (false);
	data->win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, window_title);
	if (data->win == NULL)
		return (false);
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (data->img == NULL)
		return (false);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	if (data->addr == NULL)
		return (false);
	return (true);
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
	if (!initialize_mlx(&data, argv[0]))
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
