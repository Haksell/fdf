/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 18:22:58 by axbrisse          #+#    #+#             */
/*   Updated: 2022/12/16 22:58:24 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

static void	pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	dst = data->addr + data->line_length * y + data->bits_per_pixel / 8 * x;
	*(unsigned int *)dst = color;
}

void	calculate_pixel(t_data *data, int x, int y, t_iteration_func func)
{
	static t_color_func	color_funcs[] = {
		get_color_0, get_color_1, get_color_2, get_color_3, get_color_4,
		get_color_5, get_color_6, get_color_7, get_color_8, get_color_9,
	};
	const t_color_func	color_func = color_funcs[data->colormap];
	const double		scaled_x = scale_x(x, data);
	const double		scaled_y = scale_y(y, data);
	const int			iterations = func(scaled_x, scaled_y, data);

	pixel_put(data, x, y, color_func(iterations, MAX_ITERATIONS));
}
