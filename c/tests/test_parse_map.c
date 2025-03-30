/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 08:40:52 by axbrisse          #+#    #+#             */
/*   Updated: 2023/02/07 11:04:59 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_test.h"

void display_title(char* s) { ft_printf(BOLDBLUE "--- %s ---\n" RESET, s); }

void ft_assert(char* test_name, bool result, bool expected) {
    char* color;
    char* verdict;

    if (result == expected) {
        color = GREEN;
        verdict = "OK";
    } else {
        color = RED;
        verdict = "KO";
    }
    ft_printf("%s%s: %s\n" RESET, color, test_name, verdict);
}

t_list* ls(char* path) {
    DIR* dp;
    struct dirent* ep;
    t_list* lst;

    lst = NULL;
    dp = opendir(path);
    ep = readdir(dp);
    while (ep != NULL) {
        if (ep->d_name[0] != '.') ft_lstadd_front(&lst, ft_lstnew(ft_strjoin(path, ep->d_name)));
        ep = readdir(dp);
    }
    closedir(dp);
    ft_lst_sort(lst, (int (*)(void*, void*))ft_strcmp);
    return (lst);
}

void test(char* title, char* directory, bool expected) {
    t_map map;
    char* filename;
    t_list* filenames;

    display_title(title);
    filenames = ls(directory);
    if (!expected) ft_lstadd_front(&filenames, ft_lstnew("maps/invalid/notfound.fdf"));
    while (filenames != NULL) {
        filename = filenames->content;
        ft_assert(filename, parse_map(filename, &map), expected);
        filenames = filenames->next;
    }
}

int main(void) {
    test("VALID MAPS", VALID_DIRECTORY, true);
    chmod("maps/invalid/unreadable.fdf", 0000);
    test("INVALID MAPS", INVALID_DIRECTORY, false);
    chmod("maps/invalid/unreadable.fdf", 0644);
}
