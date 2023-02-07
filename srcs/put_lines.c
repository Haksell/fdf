/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_lines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 03:48:33 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/07 14:21:51 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	lerp_component(int c0, int c1, int dist, int dist_max)
{
	return ((c0 * dist + c1 * (dist_max - dist)) / dist_max);
}

static int	lerp_color(
	t_int_vertex *v0,
	t_int_vertex *v1,
	const t_int_vertex *dv
)
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

static void	colorize_pixel(t_data *data, t_int_vertex *v, int color)
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

static t_int_vertex	create_int_vertex(t_vertex *vertex)
{
	t_int_vertex	int_vertex;

	int_vertex.x = (int)vertex->x;
	int_vertex.y = (int)vertex->y;
	int_vertex.z = (int)vertex->z;
	int_vertex.color = vertex->color;
	return (int_vertex);
}

static t_int_vertex	get_shift_vector(t_int_vertex *v0, t_int_vertex *v1)
{
	return ((t_int_vertex){
		get_sign(v1->x - v0->x),
		get_sign(v1->y - v0->y),
		get_sign(v1->z - v0->z), 0});
}

static void	bresenham_x(
	t_data *data,
	t_int_vertex *v0,
	t_int_vertex *v1,
	const t_int_vertex *dv
)
{
	const t_int_vertex	sv = get_shift_vector(v0, v1);
	int					p1;
	int					p2;

	p1 = 2 * dv->y - dv->x;
	p2 = 2 * dv->z - dv->x;
	while (v0->x != v1->x)
	{
		v0->x += sv.x;
		if (p1 >= 0)
		{
			v0->y += sv.y;
			p1 -= 2 * dv->x;
		}
		if (p2 >= 0)
		{
			v0->z += sv.z;
			p2 -= 2 * dv->x;
		}
		p1 += 2 * dv->y;
		p2 += 2 * dv->z;
		colorize_pixel(data, v0, lerp_color(v0, v1, dv));
	}
}

static void	bresenham_y(
	t_data *data,
	t_int_vertex *v0,
	t_int_vertex *v1,
	const t_int_vertex *dv
)
{
	const t_int_vertex	sv = get_shift_vector(v0, v1);
	int					p1;
	int					p2;

	p2 = 2 * dv->z - dv->y;
	p1 = 2 * dv->x - dv->y;
	while (v0->y != v1->y)
	{
		v0->y += sv.y;
		if (p1 >= 0)
		{
			v0->x += sv.x;
			p1 -= 2 * dv->y;
		}
		if (p2 >= 0)
		{
			v0->z += sv.z;
			p2 -= 2 * dv->y;
		}
		p1 += 2 * dv->x;
		p2 += 2 * dv->z;
		colorize_pixel(data, v0, lerp_color(v0, v1, dv));
	}
}

static void	bresenham_z(
	t_data *data,
	t_int_vertex *v0,
	t_int_vertex *v1,
	const t_int_vertex *dv
)
{
	const t_int_vertex	sv = get_shift_vector(v0, v1);
	int					p1;
	int					p2;

	p1 = 2 * dv->y - dv->z;
	p2 = 2 * dv->x - dv->z;
	while (v0->z != v1->z)
	{
		v0->z += sv.z;
		if (p1 >= 0)
		{
			v0->y += sv.y;
			p1 -= 2 * dv->z;
		}
		if (p2 >= 0)
		{
			v0->x += sv.x;
			p2 -= 2 * dv->z;
		}
		p1 += 2 * dv->y;
		p2 += 2 * dv->x;
		colorize_pixel(data, v0, lerp_color(v0, v1, dv));
	}
}

void	bresenham(t_data *data, t_int_vertex *v0, t_int_vertex *v1)
{
	const t_int_vertex	dv = {
		abs(v1->x - v0->x),
		abs(v1->y - v0->y),
		abs(v1->z - v0->z),
		0};

	colorize_pixel(data, v0, v0->color);
	if (dv.x >= dv.y && dv.x >= dv.z)
		bresenham_x(data, v0, v1, &dv);
	else if (dv.y >= dv.x && dv.y >= dv.z)
		bresenham_y(data, v0, v1, &dv);
	else
		bresenham_z(data, v0, v1, &dv);
}

void	put_lines(t_data *data, t_vertex **copy)
{
	t_int_vertex	v0;
	t_int_vertex	v1;
	int				x;
	int				y;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			v0 = create_int_vertex(&copy[y][x]);
			if (x + 1 < data->map.width)
				v1 = create_int_vertex(&copy[y][x + 1]);
			if (x + 1 < data->map.width)
				bresenham(data, &v0, &v1);
			v0 = create_int_vertex(&copy[y][x]);
			if (y + 1 < data->map.height)
				v1 = create_int_vertex(&copy[y + 1][x]);
			if (y + 1 < data->map.height)
				bresenham(data, &v0, &v1);
			++x;
		}
		++y;
	}
}
