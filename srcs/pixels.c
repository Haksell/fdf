/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:47:59 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/07 14:49:13 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + data->line_length * y + data->bits_per_pixel / 8 * x;
	*(unsigned int *)dst = color;
}

void	colorize_pixel(t_data *data, t_int_vertex *v, int color)
{
	if (
		0 <= v->x && v->x < WINDOW_WIDTH && 0 <= v->y && v->y < WINDOW_HEIGHT
		&& v->z > data->colors[v->y][v->x].z
	)
	{
		data->colors[v->y][v->x].z = v->z;
		data->colors[v->y][v->x].color = color;
	}
}

int	lerp_component(int c0, int c1, int dist, int dist_max)
{
	return ((c0 * dist + c1 * (dist_max - dist)) / dist_max);
}

int	lerp_color(t_int_vertex *v0, t_int_vertex *v1, const t_int_vertex *dv)
{
	const int	c0 = v0->color;
	const int	c1 = v1->color;
	const int	dist_max = dv->x + dv->y + dv->z;
	const int	dist = (
			abs(v1->x - v0->x)
			+ abs(v1->y - v0->y)
			+ abs(v1->z - v0->z));

	if (dist_max == 0)
		return (c0);
	return (
		lerp_component(c0 >> 16, c1 >> 16, dist, dist_max) << 16
		| lerp_component(c0 >> 8 & 255, c1 >> 8 & 255, dist, dist_max) << 8
		| lerp_component(c0 & 255, c1 & 255, dist, dist_max)
	);
}
