/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_lines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 03:48:33 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/06 08:21:23 by axbrisse         ###   ########.fr       */
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

static void	colorize_pixel(t_data *data, t_int_vertex *vertex, int color)
{
    if (
        0 <= vertex->x && vertex->x < WINDOW_WIDTH && 0 <= vertex->y && vertex->y < WINDOW_HEIGHT
		&& vertex->z > data->colors[vertex->y][vertex->x].z
    )
    {
        data->colors[vertex->y][vertex->x].z = vertex->z;
        data->colors[vertex->y][vertex->x].color = color;
    }
}

static t_int_vertex    create_int_vertex(t_vertex *vertex)
{
    t_int_vertex    int_vertex;

    int_vertex.x = (int)vertex->x;
    int_vertex.y = (int)vertex->y;
    int_vertex.z = (int)vertex->z;
    int_vertex.color = vertex->color;
    return (int_vertex);
}

void    line(t_data *data, t_int_vertex v0, t_int_vertex v1)
{
	const t_int_vertex	dv = {abs(v1.x - v0.x), abs(v1.y - v0.y), abs(v1.z - v0.z), 0};
	const t_int_vertex	sv = {get_sign(v1.x - v0.x), get_sign(v1.y - v0.y), get_sign(v1.z - v0.z), 0};
	
    colorize_pixel(data, &v0, v0.color);
    if (dv.x >= dv.y && dv.x >= dv.z) {
        int p1 = 2 * dv.y - dv.x;
        int p2 = 2 * dv.z - dv.x;
        while (v0.x != v1.x) {
            v0.x += sv.x;
            if (p1 >= 0) {
                v0.y += sv.y;
                p1 -= 2 * dv.x;
            }
            if (p2 >= 0) {
                v0.z += sv.z;
                p2 -= 2 * dv.x;
            }
            p1 += 2 * dv.y;
            p2 += 2 * dv.z;
            colorize_pixel(data, &v0, lerp_color(v0.color, v1.color, abs(v1.x - v0.x) + abs(v1.y - v0.y) + abs(v1.z - v0.z), dv.x + dv.y + dv.z));
        }
    }
    else if (dv.y >= dv.x && dv.y >= dv.z) {
        int p1 = 2 * dv.x - dv.y;
        int p2 = 2 * dv.z - dv.y;
        while (v0.y != v1.y) {
            v0.y += sv.y;
            if (p1 >= 0) {
                v0.x += sv.x;
                p1 -= 2 * dv.y;
            }
            if (p2 >= 0) {
                v0.z += sv.z;
                p2 -= 2 * dv.y;
            }
            p1 += 2 * dv.x;
            p2 += 2 * dv.z;
            colorize_pixel(data, &v0, lerp_color(v0.color, v1.color, abs(v1.x - v0.x) + abs(v1.y - v0.y) + abs(v1.z - v0.z), dv.x + dv.y + dv.z));
        }
    }
    else {
        int p1 = 2 * dv.y - dv.z;
        int p2 = 2 * dv.x - dv.z;
        while (v0.z != v1.z) {
            v0.z += sv.z;
            if (p1 >= 0) {
                v0.y += sv.y;
                p1 -= 2 * dv.z;
            }
            if (p2 >= 0) {
                v0.x += sv.x;
                p2 -= 2 * dv.z;
            }
            p1 += 2 * dv.y;
            p2 += 2 * dv.x;
            colorize_pixel(data, &v0, lerp_color(v0.color, v1.color, abs(v1.x - v0.x) + abs(v1.y - v0.y) + abs(v1.z - v0.z), dv.x + dv.y + dv.z));
        }
    }
}

void	put_lines(t_data *data, t_vertex **copy)
{
    for (int y = 0; y < data->map.height; ++y)
    {
        for (int x = 0; x < data->map.width; ++x)
        {
            if (x + 1 < data->map.width)
                line(data, create_int_vertex(&copy[y][x]), create_int_vertex(&copy[y][x + 1]));
            if (y + 1 < data->map.height)
                line(data, create_int_vertex(&copy[y][x]), create_int_vertex(&copy[y + 1][x]));
        }
    }
}