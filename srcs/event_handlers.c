/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 05:44:19 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/03 04:57:02 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_window(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
	return (0);
}

int	handle_key_down(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		close_window(data);
	// TODO if (!data->is_bonus) return (0);
	data->is_modified = true;
	if (keycode == KEY_LEFT)
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
		data->params.rx += 0.2;
	else if (keycode == 'x')
		data->params.rx -= 0.2;
	else if (keycode == 'r')
		init_params(data);
	else
		data->is_modified = false;
	return (0);
}

int	handle_mouse_down(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	// TODO if (!data->is_bonus) return (0);
	data->is_modified = true;
	if (button == SCROLL_UP)
		data->params.scale *= SCALE_SHIFT;
	else if (button == SCROLL_DOWN)
		data->params.scale /= SCALE_SHIFT;
	else
		data->is_modified = false;
	return (0);
}
