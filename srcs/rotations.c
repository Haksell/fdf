/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 08:34:00 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/06 08:34:08 by axbrisse         ###   ########.fr       */
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
	rotate_2d(&vertex->x, &vertex->y, rz);
	rotate_2d(&vertex->z, &vertex->x, ry);
	rotate_2d(&vertex->y, &vertex->z, rx);
}

void	inverse_rotate_vertex(t_vertex *vertex, double rx, double ry, double rz)
{
	rotate_2d(&vertex->y, &vertex->z, -rx);
	rotate_2d(&vertex->z, &vertex->x, -ry);
	rotate_2d(&vertex->x, &vertex->y, -rz);
}
