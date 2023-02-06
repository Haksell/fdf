/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 08:30:46 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/06 11:28:27 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	project_cabinet(t_vertex *vertex, t_data *data)
{
	(void)data;
	vertex->x += vertex->z * CABINET_COS;
	vertex->y += vertex->z * CABINET_SIN;
	vertex->z = 0;
}

static void	project_parallel_side(t_vertex *vertex, t_data *data)
{
	(void)data;
	vertex->y = -vertex->z;
}

static void	project_isometric(t_vertex *vertex, t_data *data)
{
	const double	tmp_x = vertex->x;
	const double	tmp_y = vertex->y - data->map.height + 1;

	vertex->x = ISOMETRIC_COS * (tmp_y + tmp_x);
	vertex->y = ISOMETRIC_SIN * (tmp_y - tmp_x) - vertex->z;
}

void	project_vertex(t_vertex *vertex, t_data *data)
{
	static t_project_func	funcs[] = {
		[CABINET] = project_cabinet,
		[PARALLEL_TOP] = NULL,
		[PARALLEL_SIDE] = project_parallel_side,
		[ISOMETRIC] = project_isometric,
	};
	const t_project_func	func = funcs[data->projection];

	if (func != NULL)
		func(vertex, data);
}

static void	inverse_project_isometric(t_vertex *vertex, t_data *data)
{
	static double	cs2 = ISOMETRIC_COS * ISOMETRIC_SIN * 2.0;
	const double	tmp_x = vertex->x;
	const double	tmp_y = vertex->y;

	vertex->x = (ISOMETRIC_SIN * tmp_x - ISOMETRIC_COS * tmp_y) / cs2;
	vertex->y = (ISOMETRIC_SIN * tmp_x + ISOMETRIC_COS * tmp_y) / cs2 + data->map.height - 1;
}

void	inverse_project_vertex(t_vertex *vertex, t_data *data)
{
	static t_project_func	funcs[] = {
		[CABINET] = NULL,
		[PARALLEL_TOP] = NULL,
		[PARALLEL_SIDE] = NULL,
		[ISOMETRIC] = inverse_project_isometric,
	};
	const t_project_func	func = funcs[data->projection];

	if (func != NULL)
		func(vertex, data);
}
