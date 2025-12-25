#include "draw.h"
#include <stdlib.h>

// algorythm of Brathenham for line
void draw_line(Buffer* buffer, Coord* coord, char ch) {
    if (!buffer || !coord) return;

    int x1 = coord->x[FIRST];
    int y1 = coord->y[FIRST];
    int x2 = coord->x[SECOND];
    int y2 = coord->y[SECOND];

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        // using set_pixel from buffer.c
        // this feature is need to be added to buffer.h
        // for now, just a direct appeal
        if (x1 >= 0 && x1 < buffer->cols &&
            y1 >= 0 && y1 < buffer->rows) {
            buffer->data[y1][x1] = ch;
        }

        if (x1 == x2 && y1 == y2) break;

        int e2 = err * 2;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

// rectangle
void draw_rect(Buffer* buffer, Coord* coord, char ch) {
    if (!buffer) return;

    int x1 = coord->x[FIRST];
    int y1 = coord->y[FIRST];
    int x2 = coord->x[SECOND];
    int y2 = coord->y[SECOND];

    // checking & organazing coordinates
    if (x1 > x2) { int temp = x1; x1 = x2; x2 = temp; }
    if (y1 > y2) { int temp = y1; y1 = y2; y2 = temp; }

    // top & bottom sides
    for (int x = x1; x <= x2; x++) {
        if (x >= 0 && x < buffer->cols) {
            if (y1 >= 0 && y1 < buffer->rows) buffer->data[y1][x] = ch;
            if (y2 >= 0 && y2 < buffer->rows) buffer->data[y2][x] = ch;
        }
    }

    // left & right sides
    for (int y = y1; y <= y2; y++) {
        if (y >= 0 && y < buffer->rows) {
            if (x1 >= 0 && x1 < buffer->cols) buffer->data[y][x1] = ch;
            if (x2 >= 0 && x2 < buffer->cols) buffer->data[y][x2] = ch;
        }
    }
}
