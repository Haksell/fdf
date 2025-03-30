/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 05:44:19 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/07 14:38:46 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

static void zoom(t_data* data, int x, int y, double scale_shift) {
    t_vertex mouse;

    mouse.x = x;
    mouse.y = y;
    mouse.z = 0;
    inverse_transform_vertex(&mouse, data);
    data->params.scale *= scale_shift;
    transform_vertex(&mouse, data);
    data->params.tx += x - mouse.x;
    data->params.ty += y - mouse.y;
}

int handle_mouse_down(int button, int x, int y, t_data* data) {
    if (button == BUTTON_LEFT) {
        data->mouse.x = x;
        data->mouse.y = y;
    } else if (button == SCROLL_UP) {
        data->should_rerender = true;
        zoom(data, x, y, SCALE_SHIFT);
    } else if (button == SCROLL_DOWN) {
        data->should_rerender = true;
        zoom(data, x, y, 1 / SCALE_SHIFT);
    }
    return (EXIT_SUCCESS);
}

int handle_mouse_up(int button, int x, int y, t_data* data) {
    if (button == BUTTON_LEFT) {
        data->should_rerender = true;
        data->params.tx += x - data->mouse.x;
        data->params.ty += y - data->mouse.y;
    }
    return (EXIT_SUCCESS);
}
