/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 01:35:04 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/06 02:19:04 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_2d(double *d1, double *d2, double rotation)
{
	const double	dist = hypot(*d1, *d2);
	const double	angle = atan2(*d2, *d1) + rotation;

	*d1 = dist * cos(angle);
	*d2 = dist * sin(angle);
}

void	rotate_vertex(t_vertex *vertex, double rx, double ry, double rz)
{
	rotate_2d(&vertex->y, &vertex->z, rx);
	rotate_2d(&vertex->z, &vertex->x, ry);
	rotate_2d(&vertex->x, &vertex->y, rz);
}

void	scale_vertex(t_vertex *vertex, double scale)
{
	vertex->x *= scale;
	vertex->y *= scale;
	vertex->z *= scale;
}

void	project_vertex(t_vertex *vertex, double height)
{
	// TODO switch on params.projection
	const double	tmp_x = vertex->x;
	const double	tmp_y = vertex->y - height + 1;

	vertex->x = ISOCOS * (tmp_y + tmp_x);
	vertex->y = ISOSIN * (tmp_y - tmp_x) - vertex->z;
}

void	translate_vertex(t_vertex *vertex, double tx, double ty)
{
	vertex->x += tx;
	vertex->y += ty;
}

void	inverse_project_vertex(t_vertex *vertex, double height)
{
	// TODO switch on params.projection
	static double	cs2 = ISOCOS * ISOSIN * 2.0;
	const double	tmp_x = vertex->x;
	const double	tmp_y = vertex->y;

	vertex->x = (ISOSIN * tmp_x - ISOCOS * tmp_y) / cs2;
	vertex->y = (ISOSIN * tmp_x + ISOCOS * tmp_y) / cs2 + height - 1;
}

void	transform_vertex(t_vertex *vertex, t_data *data)
{
	scale_vertex(vertex, data->params.scale);
	rotate_vertex(vertex, data->params.rx, data->params.ry, data->params.rz);
	project_vertex(vertex, data->map.height);
	translate_vertex(vertex, data->params.tx, data->params.ty);
}

void	inverse_transform_vertex(t_vertex *vertex, t_data *data)
{
	translate_vertex(vertex, -data->params.tx, -data->params.ty);
	inverse_project_vertex(vertex, data->map.height);
	rotate_vertex(vertex, -data->params.rx, -data->params.ry, -data->params.rz);
	// rotate_2d(&vertex->x, &vertex->y, -data->params.rz);
	// rotate_2d(&vertex->z, &vertex->x, -data->params.ry);
	// rotate_2d(&vertex->y, &vertex->z, -data->params.rx);
	scale_vertex(vertex, 1.0 / data->params.scale);
}

void	transform_vertices(t_data *data, t_vertex **copy)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			transform_vertex(&copy[y][x], data);
			++x;
		}
		++y;
	}
}