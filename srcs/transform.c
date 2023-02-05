/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 01:35:04 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/05 01:50:14 by axbrisse         ###   ########.fr       */
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

void	rotate_vertex(t_vertex *vertex, t_params *params)
{
	rotate_2d(&vertex->y, &vertex->z, params->rx);
	rotate_2d(&vertex->z, &vertex->x, params->ry);
	rotate_2d(&vertex->x, &vertex->y, params->rz);
}

void	scale_vertex(t_vertex *vertex, t_params *params)
{
	vertex->x *= params->scale;
	vertex->y *= params->scale;
	vertex->z *= params->scale;
}

void	project_vertex(t_vertex *vertex, double height)
{
	// TODO switch on params.projection
	const double	map_x = vertex->x;
	const double	map_y = vertex->y - height + 1;

	vertex->x = ISOMETRIC_COS * (map_y + map_x);
	vertex->y = ISOMETRIC_SIN * (map_y - map_x) - vertex->z;
}

void	translate_vertex(t_vertex *vertex, t_params *params)
{
	vertex->x += params->tx;
	vertex->y += params->ty;
}

void	transform_vertex(t_vertex *vertex, t_data *data)
{
	scale_vertex(vertex, &data->params);
	rotate_vertex(vertex, &data->params);
	project_vertex(vertex, data->map.height);
	translate_vertex(vertex, &data->params);
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