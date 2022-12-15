/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_coords.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 20:58:08 by axbrisse          #+#    #+#             */
/*   Updated: 2022/12/15 21:02:44 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static double	scale_coord(int coord, double window_size, double min_coord, double max_coord)
{
	const double	scaled_coord = (double)coord / (double)window_size;
	const double	fractal_size = max_coord - min_coord;

	return (min_coord + scaled_coord * fractal_size);
}

double	scale_x(int x, t_data *data)
{
	return (scale_coord(x, WINDOW_WIDTH, data->limits.min_x, data->limits.max_x));
}

double	scale_y(int y, t_data *data)
{
	return (scale_coord(y, WINDOW_HEIGHT, data->limits.min_y, data->limits.max_y));
}