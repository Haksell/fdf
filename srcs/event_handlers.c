/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 18:16:05 by axbrisse          #+#    #+#             */
/*   Updated: 2022/12/15 21:02:17 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
	return (0);
}

int	handle_key_down(int keycode, t_data *data)
{
	if (keycode == ESC)
		close_window(data);
	return (0);
}

void	zoom(int button, int x, int y, t_data *data)
{
	const double	x_before = scale_x(x, data);
	const double	y_before = scale_y(y, data);
	double			diff_real;
	double			diff_imag;
	size_t			i;

	i = 0;
	while (i < 4)
	{
		if (button == SCROLL_UP)
			((double *)&data->limits)[i] /= ZOOM_FACTOR;
		else
			((double *)&data->limits)[i] *= ZOOM_FACTOR;
		++i;
	}
	diff_real = x_before - scale_x(x, data);
	diff_imag = y_before - scale_y(y, data);
	data->limits.min_x += diff_real;
	data->limits.max_x += diff_real;
	data->limits.min_y += diff_imag;
	data->limits.max_y += diff_imag;
}

int	handle_zoom(int button, int x, int y, t_data *data)
{
	if (button == SCROLL_UP || button == SCROLL_DOWN)
		zoom(button, x, y, data);
	return (0);
}
