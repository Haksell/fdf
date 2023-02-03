/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 03:48:33 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/03 05:38:46 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	lerp_component(int c0, int c1, int dist, int dist_max)
{
	return ((c0 * dist + c1 * (dist_max - dist)) / dist_max);
}

static int	lerp_color(int c0, int c1, int dist, int dist_max)
{
	if (dist_max == 0)
		return (c0);
	return (
		lerp_component(c0 >> 16, c1 >> 16, dist, dist_max) << 16
		| lerp_component(c0 >> 8 & 255, c1 >> 8 & 255, dist, dist_max) << 8
		| lerp_component(c0 & 255, c1 & 255, dist, dist_max)
	);
}

void	line(t_data *data, int x0, int y0, int c0, int x1, int y1, int c1)
{
	int dx = abs(x1 - x0);
	int sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0);
	int sy = y0 < y1 ? 1 : -1;
	int error = dx + dy;
	
	// TODO return if no pixel can be drawn
	// ft_printf("before x0=%d, y0=%d, c0=%d, x1=%d, y1=%d, c1=%d\n", x0, y0, c0, x1, y1, c1);
	while (true)
	{
		pixel_put(data, x0, y0, lerp_color(c0, c1, abs(x0-x1) + abs(y0-y1), dx-dy));
		if (x0 == x1 && y0 == y1) return ;
		int e2 = 2 * error;
		if (e2 >= dy)
		{
			if (x0 == x1) return ;
			error += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			if (y0 == y1) return ;
			error += dx;
			y0 += sy;
		}
	}
}