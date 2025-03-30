#include "../../includes/fdf.h"

static t_int_vertex get_shift_vector(t_int_vertex* v0, t_int_vertex* v1) {
    return ((t_int_vertex){
        get_sign(v1->x - v0->x), get_sign(v1->y - v0->y), get_sign(v1->z - v0->z), 0});
}

static void bresenham_x(t_data* data, t_int_vertex* v0, t_int_vertex* v1, const t_int_vertex* dv) {
    const t_int_vertex sv = get_shift_vector(v0, v1);
    int p1;
    int p2;

    p1 = 2 * dv->y - dv->x;
    p2 = 2 * dv->z - dv->x;
    while (v0->x != v1->x) {
        v0->x += sv.x;
        if (p1 >= 0) {
            v0->y += sv.y;
            p1 -= 2 * dv->x;
        }
        if (p2 >= 0) {
            v0->z += sv.z;
            p2 -= 2 * dv->x;
        }
        p1 += 2 * dv->y;
        p2 += 2 * dv->z;
        colorize_pixel(data, v0, lerp_color(v0, v1, dv));
    }
}

static void bresenham_y(t_data* data, t_int_vertex* v0, t_int_vertex* v1, const t_int_vertex* dv) {
    const t_int_vertex sv = get_shift_vector(v0, v1);
    int p1;
    int p2;

    p2 = 2 * dv->z - dv->y;
    p1 = 2 * dv->x - dv->y;
    while (v0->y != v1->y) {
        v0->y += sv.y;
        if (p1 >= 0) {
            v0->x += sv.x;
            p1 -= 2 * dv->y;
        }
        if (p2 >= 0) {
            v0->z += sv.z;
            p2 -= 2 * dv->y;
        }
        p1 += 2 * dv->x;
        p2 += 2 * dv->z;
        colorize_pixel(data, v0, lerp_color(v0, v1, dv));
    }
}

static void bresenham_z(t_data* data, t_int_vertex* v0, t_int_vertex* v1, const t_int_vertex* dv) {
    const t_int_vertex sv = get_shift_vector(v0, v1);
    int p1;
    int p2;

    p1 = 2 * dv->y - dv->z;
    p2 = 2 * dv->x - dv->z;
    while (v0->z != v1->z) {
        v0->z += sv.z;
        if (p1 >= 0) {
            v0->y += sv.y;
            p1 -= 2 * dv->z;
        }
        if (p2 >= 0) {
            v0->x += sv.x;
            p2 -= 2 * dv->z;
        }
        p1 += 2 * dv->y;
        p2 += 2 * dv->x;
        colorize_pixel(data, v0, lerp_color(v0, v1, dv));
    }
}

void bresenham(t_data* data, t_int_vertex* v0, t_int_vertex* v1) {
    const t_int_vertex dv = {abs(v1->x - v0->x), abs(v1->y - v0->y), abs(v1->z - v0->z), 0};

    colorize_pixel(data, v0, v0->color);
    if (dv.x >= dv.y && dv.x >= dv.z)
        bresenham_x(data, v0, v1, &dv);
    else if (dv.y >= dv.x && dv.y >= dv.z)
        bresenham_y(data, v0, v1, &dv);
    else
        bresenham_z(data, v0, v1, &dv);
}
