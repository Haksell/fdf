#include "../../includes/fdf.h"

static bool handle_numpad(int keycode, t_data* data) {
    static int numpad[10] = {7, 4, 8, 6, 2, 9, 3, 1, 5, 0};
    t_projection projection;

    if (keycode < MIN_NUMPAD || keycode > MAX_NUMPAD) return (false);
    projection = numpad[keycode - MIN_NUMPAD];
    if (projection == data->projection || projection > MAX_PROJECTION) return (false);
    data->projection = projection;
    init_params(data);
    return (true);
}

static bool handle_special(int keycode, t_data* data) {
    if (keycode == KEY_HOME)
        init_params(data);
    else if (keycode == KEY_LEFT)
        data->params.tx -= TRANSLATION;
    else if (keycode == KEY_UP)
        data->params.ty -= TRANSLATION;
    else if (keycode == KEY_RIGHT)
        data->params.tx += TRANSLATION;
    else if (keycode == KEY_DOWN)
        data->params.ty += TRANSLATION;
    else
        return (false);
    return (true);
}

static bool handle_letters(int keycode, t_data* data) {
    if (keycode == 'i')
        data->params.altitude /= ALTITUDE_SHIFT;
    else if (keycode == 'o')
        data->params.altitude = -data->params.altitude;
    else if (keycode == 'p')
        data->params.altitude *= ALTITUDE_SHIFT;
    else if (keycode == 'w')
        data->params.rx += ANGLE_SHIFT;
    else if (keycode == 's')
        data->params.rx -= ANGLE_SHIFT;
    else if (keycode == 'd')
        data->params.ry += ANGLE_SHIFT;
    else if (keycode == 'a')
        data->params.ry -= ANGLE_SHIFT;
    else if (keycode == 'k')
        data->params.rz += ANGLE_SHIFT;
    else if (keycode == 'l')
        data->params.rz -= ANGLE_SHIFT;
    else
        return (false);
    return (true);
}

int handle_key_down(int keycode, t_data* data) {
    if (keycode == KEY_ESC) close_window(data);
    data->should_rerender =
        (handle_numpad(keycode, data) || handle_special(keycode, data)
         || handle_letters(keycode, data));
    return (EXIT_SUCCESS);
}
