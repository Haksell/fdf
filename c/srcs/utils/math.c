#include "../../includes/fdf.h"

double get_min(double x1, double x2) {
    if (x1 < x2)
        return (x1);
    else
        return (x2);
}

double get_max(double x1, double x2) {
    if (x1 > x2)
        return (x1);
    else
        return (x2);
}

int get_sign(int n) { return ((n > 0) - (n < 0)); }
