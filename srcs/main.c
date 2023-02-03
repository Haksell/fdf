/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:04:35 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/03 05:02:02 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h> // TODO

bool	is_close(double d0, double d1)
{
	const double	diff = d0 - d1;

	return (-EPSILON < diff && diff < EPSILON);
}

void	translate(t_data *data, double **points, double translation)
{
	int	i;
	int	j;

	i = 0;
	if (is_close(translation, 0.0))
		return ;
	while (i < data->map.height)
	{
		j = 0;
		while (j < data->map.width)
		{
			points[i][j] += translation;
			++j;
		}
		++i;
	}
}

bool	angle_is_close_to_zero(double angle)
{
	return (is_close(fmod(angle + EPSILON / 2, M_TAU), 0));
}

void	rotate(t_data *data, double **xs, double **ys)
{
	int		i;
	int		j;
	double	dist;
	double	angle;

	i = 0;
	if (angle_is_close_to_zero(data->params.rx))
		return ;
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

int render_frame(t_data *data)
{
	double **xs;
	double **ys;

	if (!data->is_modified)
		return (EXIT_SUCCESS);
	black_background(data);
	if (!init_grid((void ***)&xs, data->map.width, data->map.height, sizeof(double))
		|| !init_grid((void ***)&ys, data->map.width, data->map.height, sizeof(double)))
		close_window(data);
	for (int y = 0; y < data->map.height; ++y)
	{
		for (int x = 0; x < data->map.width; ++x)
		{
			xs[y][x] = data->map.vertices[y][x].x;
			ys[y][x] = data->map.vertices[y][x].y;
		}
	}
	scale(data, xs, ys);
	rotate(data, xs, ys);
	translate(data, xs, data->params.tx);
	translate(data, ys, data->params.ty);
	for (int y = 0; y < data->map.height; ++y)
	{
		for (int x = 0; x < data->map.width; ++x)
		{
			if (x + 1 < data->map.width)
				line(data, (int)xs[y][x], (int)ys[y][x], data->map.vertices[y][x].color, (int)xs[y][x + 1], (int)ys[y][x + 1], data->map.vertices[y][x + 1].color);
			if (y + 1 < data->map.height)
				line(data, (int)xs[y][x], (int)ys[y][x], data->map.vertices[y][x].color, (int)xs[y + 1][x], (int)ys[y + 1][x], data->map.vertices[y + 1][x].color);
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
