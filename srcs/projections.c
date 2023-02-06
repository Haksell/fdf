/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 08:30:46 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/06 08:49:44 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	project_isometric(t_vertex *vertex, t_data *data)
{
	const double	tmp_x = vertex->x;
	const double	tmp_y = vertex->y - data->map.height + 1;

	vertex->x = ISOCOS * (tmp_y + tmp_x);
	vertex->y = ISOSIN * (tmp_y - tmp_x) - vertex->z;
}

void	project_vertex(t_vertex *vertex, t_data *data)
{
	static t_project_func	funcs[] = { project_isometric };
	const t_project_func	func = funcs[data->projection];

	func(vertex, data);
}

static void	inverse_project_isometric(t_vertex *vertex, t_data *data)
{
	static double	cs2 = ISOCOS * ISOSIN * 2.0;
	const double	tmp_x = vertex->x;
	const double	tmp_y = vertex->y;

	vertex->x = (ISOSIN * tmp_x - ISOCOS * tmp_y) / cs2;
	vertex->y = (ISOSIN * tmp_x + ISOCOS * tmp_y) / cs2 + data->map.height - 1;
}

void	inverse_project_vertex(t_vertex *vertex, t_data *data)
{
	static t_project_func	funcs[] = { inverse_project_isometric };
	const t_project_func	func = funcs[data->projection];

	func(vertex, data);
}
