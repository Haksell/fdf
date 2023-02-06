/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_lines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 03:48:33 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/06 07:37:01 by axbrisse         ###   ########.fr       */
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

static void	colorize_pixel(t_data *data, int x, int y, int z, int color)
{
    if (
        0 <= x && x < WINDOW_WIDTH && 0 <= y
        && y < WINDOW_HEIGHT &&
        z > data->colors[y][x].z
    )
    {
        data->colors[y][x].z = z;
        data->colors[y][x].color = color;
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

void    line(t_data *data, t_int_vertex v0, t_int_vertex v1) // TODO lerp color // TODO v0 v0
{
    int dx = abs(v1.x - v0.x);
    int dy = abs(v1.y - v0.y);
    int dz = abs(v1.z - v0.z);
    int xs;
    int ys;
    int zs;
    if (v1.x > v0.x)
        xs = 1;
    else
        xs = -1;
    if (v1.y > v0.y)
        ys = 1;
    else
        ys = -1;
    if (v1.z > v0.z)
        zs = 1;
    else
        zs = -1;
    colorize_pixel(data, v0.x, v0.y, v0.z, v0.color);
    if (dx >= dy && dx >= dz) {
        int p1 = 2 * dy - dx;
        int p2 = 2 * dz - dx;
        while (v0.x != v1.x) {
            v0.x += xs;
            if (p1 >= 0) {
                v0.y += ys;
                p1 -= 2 * dx;
            }
            if (p2 >= 0) {
                v0.z += zs;
                p2 -= 2 * dx;
            }
            p1 += 2 * dy;
            p2 += 2 * dz;
            colorize_pixel(data, v0.x, v0.y, v0.z, lerp_color(v0.color, v1.color, abs(v1.x - v0.x) + abs(v1.y - v0.y) + abs(v1.z - v0.z), dx + dy + dz));
        }
    }
    else if (dy >= dx && dy >= dz) {
        int p1 = 2 * dx - dy;
        int p2 = 2 * dz - dy;
        while (v0.y != v1.y) {
            v0.y += ys;
            if (p1 >= 0) {
                v0.x += xs;
                p1 -= 2 * dy;
            }
            if (p2 >= 0) {
                v0.z += zs;
                p2 -= 2 * dy;
            }
            p1 += 2 * dx;
            p2 += 2 * dz;
            colorize_pixel(data, v0.x, v0.y, v0.z, lerp_color(v0.color, v1.color, abs(v1.x - v0.x) + abs(v1.y - v0.y) + abs(v1.z - v0.z), dx + dy + dz));
        }
    }
    else {
        int p1 = 2 * dy - dz;
        int p2 = 2 * dx - dz;
        while (v0.z != v1.z) {
            v0.z += zs;
            if (p1 >= 0) {
                v0.y += ys;
                p1 -= 2 * dz;
            }
            if (p2 >= 0) {
                v0.x += xs;
                p2 -= 2 * dz;
            }
            p1 += 2 * dy;
            p2 += 2 * dx;
            colorize_pixel(data, v0.x, v0.y, v0.z, lerp_color(v0.color, v1.color, abs(v1.x - v0.x) + abs(v1.y - v0.y) + abs(v1.z - v0.z), dx + dy + dz));
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