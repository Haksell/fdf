/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 05:44:19 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/03 05:55:33 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_window(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

int	handle_key_down(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		close_window(data);
	// TODO if (!data->is_bonus) return (EXIT_SUCCESS);
	data->is_modified = true;
	if (keycode == 'r')
		init_params(data);
	else if (keycode == KEY_LEFT)
		data->params.tx -= TRANSLATION;
	else if (keycode == KEY_UP)
		data->params.ty -= TRANSLATION;
	else if (keycode == KEY_RIGHT)
		data->params.tx += TRANSLATION;
	else if (keycode == KEY_DOWN)
		data->params.ty += TRANSLATION;
	else if (keycode == 'e')
		data->params.altitude *= ALTITUDE_SHIFT;
	else if (keycode == 'd')
		data->params.altitude /= ALTITUDE_SHIFT;
	else if (keycode == 's')
		data->params.altitude = -data->params.altitude;
	else if (keycode == 'z')
		data->params.rx += ANGLE_SHIFT;
	else if (keycode == 'x')
		data->params.rx -= ANGLE_SHIFT;
	else if (keycode == 'c')
		data->params.ry += ANGLE_SHIFT;
	else if (keycode == 'v')
		data->params.ry -= ANGLE_SHIFT;
	else if (keycode == 'b')
		data->params.rz += ANGLE_SHIFT;
	else if (keycode == 'n')
		data->params.rz -= ANGLE_SHIFT;
	else
		data->is_modified = false;
	return (EXIT_SUCCESS);
}

static double	inverse_transform(double d, double td, double scale)
{
	return ((d - td) / scale);
}

static void	zoom(t_data *data, int x, int y, double scale_shift)
{
	const double	x_before = inverse_transform(x, data->params.tx, data->params.scale);
	const double	y_before = inverse_transform(y, data->params.ty, data->params.scale);
	double			diff_x;
	double			diff_y;

	data->params.scale *= scale_shift;
	diff_x = x_before - inverse_transform(x, data->params.tx, data->params.scale);
	diff_y = y_before - inverse_transform(y, data->params.ty, data->params.scale);
	data->params.tx -= diff_x * data->params.scale;
	data->params.ty -= diff_y * data->params.scale;
}

int	handle_mouse_down(int button, int x, int y, t_data *data)
{
	// TODO if (!data->is_bonus) return (EXIT_SUCCESS);
	data->is_modified = true;
	if (button == SCROLL_UP)
		zoom(data, x, y, SCALE_SHIFT);
	else if (button == SCROLL_DOWN)
		zoom(data, x, y, 1 / SCALE_SHIFT);
	else
		data->is_modified = false;
	return (EXIT_SUCCESS);
}
