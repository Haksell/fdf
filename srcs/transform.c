/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 01:35:04 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/07 11:59:19 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	project_cabinet(t_vertex *vertex, t_data *data)
{
	(void)data;
	vertex->x += vertex->z * CABINET_COS;
	vertex->y += vertex->z * CABINET_SIN;
	// vertex->z = 0;
}

void	transform_cabinet(t_vertex *vertex, t_data *data)
{
	scale_vertex(vertex, data->params.scale);
	rotate_2d(&vertex->y, &vertex->z, CABINET_ROTATION);
	project_cabinet(vertex, data);
	translate_vertex(vertex, data->params.tx, data->params.ty);
}

void	inverse_transform_cabinet(t_vertex *vertex, t_data *data)
{
	translate_vertex(vertex, -data->params.tx, -data->params.ty);
	rotate_2d(&vertex->y, &vertex->z, -CABINET_ROTATION);
	scale_vertex(vertex, 1.0 / data->params.scale);
}

static void	project_parallel(t_vertex *vertex, t_data *data)
{
	const double	tmp_y = vertex->y;

	(void)data;
	vertex->y = -vertex->z;
	vertex->z = -tmp_y;
}

void	transform_parallel(t_vertex *vertex, t_data *data)
{
	scale_vertex(vertex, data->params.scale);
	rotate_2d(&vertex->x, &vertex->y, data->params.rz);
	project_parallel(vertex, data);
	translate_vertex(vertex, data->params.tx, data->params.ty);
}

void	inverse_transform_parallel(t_vertex *vertex, t_data *data)
{
	translate_vertex(vertex, -data->params.tx, -data->params.ty);
	project_parallel(vertex, data);
	rotate_2d(&vertex->x, &vertex->y, -data->params.rz);
	scale_vertex(vertex, 1.0 / data->params.scale);
}

static void	project_isometric(t_vertex *vertex, t_data *data)
{
	const double	tmp_x = vertex->x;
	const double	tmp_y = vertex->y - data->map.height + 1;

	vertex->x = ISOMETRIC_COS * (tmp_y + tmp_x);
	vertex->y = ISOMETRIC_SIN * (tmp_y - tmp_x) - vertex->z;
}

static void	inverse_project_isometric(t_vertex *vertex, t_data *data)
{
	static double	cs2 = ISOMETRIC_COS * ISOMETRIC_SIN * 2.0;
	const double	tmp_x = vertex->x;
	const double	tmp_y = vertex->y;

	vertex->x = (ISOMETRIC_SIN * tmp_x - ISOMETRIC_COS * tmp_y) / cs2;
	vertex->y = (ISOMETRIC_SIN * tmp_x + ISOMETRIC_COS * tmp_y) / cs2 + data->map.height - 1;
}

void	transform_isometric(t_vertex *vertex, t_data *data)
{
	scale_vertex(vertex, data->params.scale);
	rotate_vertex(vertex, data->params.rx, data->params.ry, data->params.rz);
	project_isometric(vertex, data);
	translate_vertex(vertex, data->params.tx, data->params.ty);
}

void	transform_vertex(t_vertex *vertex, t_data *data)
{
	static t_transform_func	funcs[] = {
		[CABINET] = transform_cabinet,
		[PARALLEL] = transform_parallel,
		[ISOMETRIC] = transform_isometric,
	};

	funcs[data->projection](vertex, data);
}

void	inverse_transform_isometric(t_vertex *vertex, t_data *data)
{
	translate_vertex(vertex, -data->params.tx, -data->params.ty);
	inverse_project_isometric(vertex, data);
	inverse_rotate_vertex(vertex, data->params.rx, data->params.ry, data->params.rz);
	scale_vertex(vertex, 1.0 / data->params.scale);
}

void	inverse_transform_vertex(t_vertex *vertex, t_data *data)
{
	static t_transform_func	funcs[] = {
		[CABINET] = inverse_transform_cabinet,
		[PARALLEL] = inverse_transform_parallel,
		[ISOMETRIC] = inverse_transform_isometric,
	};

	funcs[data->projection](vertex, data);
}

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
