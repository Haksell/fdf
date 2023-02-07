/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_lines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 03:48:33 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/07 14:53:17 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_int_vertex	create_int_vertex(t_vertex *vertex)
{
	t_int_vertex	int_vertex;

	int_vertex.x = (int)vertex->x;
	int_vertex.y = (int)vertex->y;
	int_vertex.z = (int)vertex->z;
	int_vertex.color = vertex->color;
	return (int_vertex);
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
