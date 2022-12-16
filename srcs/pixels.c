/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 18:22:58 by axbrisse          #+#    #+#             */
/*   Updated: 2022/12/16 01:33:11 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	dst = data->addr + data->line_length * y + data->bits_per_pixel / 8 * x;
	*(unsigned int *)dst = color;
}

void	calculate_pixel(t_data *data, int x, int y, t_iteration_func func)
{
	const double	scaled_x = scale_x(x, data);
	const double	scaled_y = scale_y(y, data);
	const int		iterations = func(scaled_x, scaled_y, data);

	pixel_put(data, x, y, get_color_0(iterations, data->max_iterations));
}
