/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 05:44:19 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/05 07:07:23 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_window(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	ft_free_double_pointer((void **)data->map.vertices, data->map.height);
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

int	handle_key_down(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		close_window(data);
	// TODO if (!data->is_bonus) return (EXIT_SUCCESS);
	data->should_rerender = true;
	if (keycode == KEY_HOME)
		init_params(data);
	else if (keycode == KEY_LEFT)
		data->params.tx -= TRANSLATION;
	else if (keycode == KEY_UP)
		data->params.ty -= TRANSLATION;
	else if (keycode == KEY_RIGHT)
		data->params.tx += TRANSLATION;
	else if (keycode == KEY_DOWN)
		data->params.ty += TRANSLATION;
	else if (keycode == 'i')
		data->params.altitude /= ALTITUDE_SHIFT;
	else if (keycode == 'o')
		data->params.altitude = -data->params.altitude;
	else if (keycode == 'p')
		data->params.altitude *= ALTITUDE_SHIFT;
	else if (keycode == 'w')
		data->params.rx += ANGLE_SHIFT;
	else if (keycode == 's')
		data->params.rx -= ANGLE_SHIFT;
	else if (keycode == 'd')
		data->params.ry += ANGLE_SHIFT;
	else if (keycode == 'a')
		data->params.ry -= ANGLE_SHIFT;
	else if (keycode == 'k')
		data->params.rz += ANGLE_SHIFT;
	else if (keycode == 'l')
		data->params.rz -= ANGLE_SHIFT;
	else
		data->should_rerender = false;
	return (EXIT_SUCCESS);
}

static void	zoom(t_data *data, int x, int y, double scale_shift)
{
	t_vertex	before = {(double)x, (double)y, 0, 0};
	t_vertex	after = {(double)x, (double)y, 0, 0};

	inverse_transform_vertex(&before, data);
	data->params.scale *= scale_shift;
	inverse_transform_vertex(&after, data);
	// t_vertex	diff = {after.x - before.x, after.y - before.y, 0, 0};
	// printf("bx=%lf by=%lf\n", before.x, before.y);
	// printf("ax=%lf ay=%lf\n", after.x, after.y);
	// printf("dx=%lf dy=%lf\n\n", diff.x, diff.y);
	// data->params.tx += diff.x;
	// data->params.ty += diff.y;
}

int	handle_mouse_down(int button, int x, int y, t_data *data)
{
	// TODO if (!data->is_bonus) return (EXIT_SUCCESS);
	data->should_rerender = true;
	if (button == SCROLL_UP)
		zoom(data, x, y, SCALE_SHIFT);
	else if (button == SCROLL_DOWN)
		zoom(data, x, y, 1 / SCALE_SHIFT);
	else
		data->should_rerender = false;
	return (EXIT_SUCCESS);
}
