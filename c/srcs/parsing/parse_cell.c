#include "../../includes/fdf.h"

static bool parse_double(const char* s, double* ans) {
    size_t i;
    double sign;
    double decimal;

    i = s[0] == '-';
    sign = (s[0] != '-') - (s[0] == '-');
    *ans = 0.0;
    while (ft_isdigit(s[i])) *ans = 10 * *ans + s[i++] - '0';
    if (s[i] == '.') {
        ++i;
        decimal = 0.1;
        while (ft_isdigit(s[i])) {
            *ans += decimal * (s[i] - '0');
            decimal /= 10;
            i++;
        }
    }
    *ans *= sign;
    return (s[i] == '\0');
}

static bool parse_color(const char* s, int* color) {
    int i;

    if ((ft_strncmp(s, "0x", 2) != 0) || (s[2] == '\0')) return (false);
    *color = 0;
    i = 2;
    while (s[i] != '\0') {
        *color <<= 4;
        if (*color > WHITE)
            return (false);
        else if (ft_isdigit(s[i]))
            *color |= s[i] - 48;
        else if ('A' <= s[i] && s[i] <= 'F')
            *color |= s[i] - 55;
        else if ('a' <= s[i] && s[i] <= 'f')
            *color |= s[i] - 87;
        else
            return (false);
        ++i;
    }
    return (true);
}

bool parse_cell(char* cell, t_map* map, int x, int y) {
    const char* comma = ft_strchr(cell, ',');
    int i;

    map->vertices[y][x].x = x - (map->width - 1) / 2;
    map->vertices[y][x].y = y - (map->height - 1) / 2;
    if (comma == NULL) {
        map->vertices[y][x].color = WHITE;
        return (parse_double(cell, &map->vertices[y][x].z));
    } else {
        i = comma - cell;
        cell[i] = '\0';
        return (
            parse_double(cell, &map->vertices[y][x].z)
            && parse_color(cell + i + 1, &map->vertices[y][x].color));
    }
}
