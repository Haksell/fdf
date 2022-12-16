/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_iterations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 18:24:36 by axbrisse          #+#    #+#             */
/*   Updated: 2022/12/16 21:39:31 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

static bool	in_main_bulbs(double x, double y)
{
	const double	y_squared = y * y;
	const double	x_shift = x - 0.25;
	const double	q = x_shift * x_shift + y_squared;

	return (
		(x + 1) * (x + 1) + y_squared < 0.0625
		|| q * (q + x_shift) < y_squared * 0.25
	);
}

int	iterations_mandelbrot(double x0, double y0, t_data *data)
{
	int		n;
	double	x;
	double	y;
	double	xtemp;

	x = x0;
	y = y0;
	if (in_main_bulbs(x0, y0))
		return (data->max_iterations);
	n = 0;
	while (n < data->max_iterations && x * x + y * y <= ESCAPE_RADIUS_SQUARED)
	{
		xtemp = x * x - y * y + x0;
		y = 2 * x * y + y0;
		x = xtemp;
		++n;
	}
	return (n);
}

int	iterations_julia(double x0, double y0, t_data *data)
{
	int		n;
	double	x;
	double	y;
	double	xtemp;

	x = x0;
	y = y0;
	n = 0;
	while (n < data->max_iterations && x * x + y * y <= ESCAPE_RADIUS_SQUARED)
	{
		xtemp = x * x - y * y + data->args.julia_start_x;
		y = 2 * x * y + data->args.julia_start_y;
		x = xtemp;
		++n;
	}
	return (n);
}

int	iterations_tricorn(double x0, double y0, t_data *data)
{
	int		n;
	double	x;
	double	y;
	double	xtemp;

	x = x0;
	y = y0;
	n = 0;
	while (n < data->max_iterations && x * x + y * y <= ESCAPE_RADIUS_SQUARED)
	{
		xtemp = x * x - y * y + x0;
		y = -2 * x * y + y0;
		x = xtemp;
		++n;
	}
	return (n);
}

int	iterations_burning_ship(double x0, double y0, t_data *data)
{
	int		n;
	double	x;
	double	y;
	double	xtemp;

	x = x0;
	y = y0;
	n = 0;
	while (n < data->max_iterations && x * x + y * y <= ESCAPE_RADIUS_SQUARED)
	{
		xtemp = x * x - y * y + x0;
		y = fabs(2 * x * y) + y0;
		x = xtemp;
		++n;
	}
	return (n);
}

int	iterations_cactus(double x0, double y0, t_data *data)
{
	int		n;
	double	x;
	double	y;
	double	xtemp;

	x = x0;
	y = y0;
	n = 0;
	while (n < data->max_iterations && x * x + y * y <= ESCAPE_RADIUS_SQUARED)
	{
		xtemp = x*x*x - 3*x*y*y + x0*x - y0*y - x - x0;
		y = 3*x*x*y - y*y*y + x0*y + x*y0 -y - y0;
		x = xtemp;
		++n;
	}
	return (n);
}

int	iterations_hmmm(double x0, double y0, t_data *data)
{
	int		n;
	double	x;
	double	y;
	double	xtemp;

	x = x0;
	y = y0;
	n = 0;
	while (n < data->max_iterations && x * x + y * y <= ESCAPE_RADIUS_SQUARED)
	{
		xtemp = x * x - y * y + x0;
		y =  x * y + y0;
		x = xtemp;
		++n;
	}
	return (n);
}
