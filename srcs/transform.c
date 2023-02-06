/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 01:35:04 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/06 08:38:33 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	scale_vertex(t_vertex *vertex, double scale)
{
	vertex->x *= scale;
	vertex->y *= scale;
	vertex->z *= scale;
}

void	translate_vertex(t_vertex *vertex, double tx, double ty)
{
	vertex->x += tx;
	vertex->y += ty;
}

void	transform_vertex(t_vertex *vertex, t_data *data)
{
	scale_vertex(vertex, data->params.scale);
	rotate_vertex(vertex, data->params.rx, data->params.ry, data->params.rz);
	project_vertex(vertex, data);
	translate_vertex(vertex, data->params.tx, data->params.ty);
}

void	inverse_transform_vertex(t_vertex *vertex, t_data *data)
{
	translate_vertex(vertex, -data->params.tx, -data->params.ty);
	inverse_project_vertex(vertex, data);
	inverse_rotate_vertex(vertex, data->params.rx, data->params.ry, data->params.rz);
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
