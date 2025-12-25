#ifndef COORD_H
#define COORD_H

#include <stdbool.h>
#include <sys/ioctl.h>

// for coordinates first/second x/y
#define FIRST 0
#define SECOND 1

// coordinates structure
typedef struct {
    int x[2];
    int y[2];
} Coord;

// function prototypes
bool set_coordinate(struct winsize *w, Coord *coord,
                    int x1, int y1, int x2, int y2);

#endif // COORD_H
