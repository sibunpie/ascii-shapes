#include <stdio.h>
#include <stdlib.h>
#include "coord.h"

bool set_coordinate(struct winsize *w, Coord *coord,
                    int x1, int y1, int x2, int y2) {

    // coordinates check
    if (x1 < 0 || x1 >= w->ws_col ||
        x2 < 0 || x2 >= w->ws_col ||
        y1 < 0 || y1 >= w->ws_row ||
        y2 < 0 || y2 >= w->ws_row) {
        fprintf(stderr, "Error: Incorrect coordinates\n");
        return false;
    }

    // set coordinates
    coord->x[FIRST]  = x1;
    coord->x[SECOND] = x2;
    coord->y[FIRST]  = y1;
    coord->y[SECOND] = y2;

    return true;
}
