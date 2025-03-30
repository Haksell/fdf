/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 06:27:14 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/07 15:42:07 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/fdf.h"

static bool get_map_dimensions(char* filename, t_map* map) {
    const int fd = open(filename, O_RDONLY);
    char* line;
    bool is_rectangle;

    if (fd < 0) return (false);
    line = get_next_line(fd);
    if (line == NULL) return (false);
    map->width = ft_num_words(line, SPACES);
    map->height = 0;
    is_rectangle = true;
    while (line != NULL) {
        if (ft_num_words(line, SPACES) != (size_t)map->width) is_rectangle = false;
        ++map->height;
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return (is_rectangle && map->height >= 2 && map->width >= 2);
}

static bool parse_row(int y, char* line, t_map* map) {
    char** cells;
    bool is_valid_row;
    char* trimmed;
    int x;

    is_valid_row = true;
    trimmed = ft_strtrim(line, SPACES);
    if (trimmed == NULL || ft_num_words(trimmed, SPACES) != (size_t)map->width)
        return (free(trimmed), false);
    cells = ft_split_set(trimmed, SPACES);
    free(trimmed);
    if (cells == NULL) return (false);
    x = 0;
    while (is_valid_row && x < map->width) {
        if (!parse_cell(cells[x], map, x, y)) is_valid_row = false;
        ++x;
    }
    ft_free_double_pointer((void***)&cells, map->width);
    return (is_valid_row);
}

bool parse_map(char* filename, t_map* map) {
    int fd;
    char* line;
    int y;
    bool is_valid_map;

    fd = open(filename, O_RDONLY);
    if (fd < 0 || !get_map_dimensions(filename, map)) return (close(fd), false);
    map->vertices = init_vertices(map->width, map->height);
    if (map->vertices == NULL) return (close(fd), false);
    is_valid_map = true;
    y = 0;
    while (is_valid_map && y < map->height) {
        line = get_next_line(fd);
        if (line == NULL || !parse_row(y, line, map)) is_valid_map = false;
        free(line);
        ++y;
    }
    close(fd);
    if (!is_valid_map) ft_free_double_pointer((void***)&map->vertices, map->height);
    return (is_valid_map);
}
