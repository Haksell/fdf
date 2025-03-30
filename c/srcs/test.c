#include "../fdf.h"

#define RESET "\033[0m"
#define BOLDBLUE "\033[1m\033[34m"
#define RED "\033[31m"
#define GREEN "\033[32m"

#define VALID_DIRECTORY "../maps/valid/"
#define INVALID_DIRECTORY "../maps/invalid/"

void display_title(char* s) { ft_printf(BOLDBLUE "--- %s ---\n" RESET, s); }

void ft_assert(char* test_name, bool result, bool expected) {
    char* color = result == expected ? GREEN : RED;
    char* verdict = result == expected ? "OK" : "KO";
    ft_printf("%s%s: %s\n" RESET, color, test_name, verdict);
}

t_list* ls(char* path) {
    t_list* lst = NULL;
    DIR* dp = opendir(path);
    struct dirent* ep = readdir(dp);
    while (ep != NULL) {
        if (ep->d_name[0] != '.') ft_lstadd_front(&lst, ft_lstnew(ft_strjoin(path, ep->d_name)));
        ep = readdir(dp);
    }
    closedir(dp);
    ft_lst_sort(lst, (int (*)(void*, void*))ft_strcmp);
    return (lst);
}

void test(char* title, char* directory, bool expected) {
    display_title(title);
    t_list* filenames = ls(directory);
    if (!expected) ft_lstadd_front(&filenames, ft_lstnew("../maps/invalid/notfound.fdf"));
    while (filenames != NULL) {
        char* filename = filenames->content;
        t_map map;
        ft_assert(filename, parse_map(filename, &map), expected);
        filenames = filenames->next;
    }
}

int main(void) {
    test("VALID MAPS", VALID_DIRECTORY, true);
    chmod("../maps/invalid/unreadable.fdf", 0000);
    test("INVALID MAPS", INVALID_DIRECTORY, false);
    chmod("../maps/invalid/unreadable.fdf", 0644);
}
