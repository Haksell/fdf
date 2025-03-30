/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cabinet.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:13:40 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/07 16:13:46 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

static void project_cabinet(t_vertex* vertex, t_data* data) {
    (void)data;
    vertex->x += vertex->z * CABINET_COS;
    vertex->y += vertex->z * CABINET_SIN;
}

void transform_cabinet(t_vertex* vertex, t_data* data) {
    scale_vertex(vertex, data->params.scale);
    rotate_2d(&vertex->y, &vertex->z, CABINET_ROTATION);
    project_cabinet(vertex, data);
    translate_vertex(vertex, data->params.tx, data->params.ty);
}

void inverse_transform_cabinet(t_vertex* vertex, t_data* data) {
    translate_vertex(vertex, -data->params.tx, -data->params.ty);
    rotate_2d(&vertex->y, &vertex->z, -CABINET_ROTATION);
    scale_vertex(vertex, 1.0 / data->params.scale);
}
