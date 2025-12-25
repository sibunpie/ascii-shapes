#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"

// create buffer
Buffer* create_buffer(struct winsize *w) {
    Buffer* buffer = malloc(sizeof(Buffer));
    if (!buffer) return NULL;

    buffer->rows = w->ws_row;
    buffer->cols = w->ws_col;

    // allocate memory
    buffer->data = malloc(buffer->rows * sizeof(char*));
    if (!buffer->data) {
        free(buffer);
        return NULL;
    }

    // allocate memory for each line
    for (int y = 0; y < buffer->rows; y++) {
        buffer->data[y] = malloc(buffer->cols * sizeof(char));
        if (!buffer->data[y]) {
            // freeing already allocated memory
            for (int i = 0; i < y; i++) {
                free(buffer->data[i]);
            }
            free(buffer->data);
            free(buffer);
            return NULL;
        }
    }

    // fill in the blanks
    clear_buffer(buffer);

    return buffer;
}

// freeing memory
void destroy_buffer(Buffer* buffer) {
    if (!buffer) return;

    if (buffer->data) {
        for (int y = 0; y < buffer->rows; y++) {
            if (buffer->data[y]) {
                free(buffer->data[y]);
            }
        }
        free(buffer->data);
    }
    free(buffer);
}

// clear buffer (fill in the blanks)
void clear_buffer(Buffer* buffer) {
    if (!buffer || !buffer->data) return;

    for (int y = 0; y < buffer->rows; y++) {
        for (int x = 0; x < buffer->cols; x++) {
            buffer->data[y][x] = ' ';
        }
    }
}

// get char
char get_pixel(Buffer* buffer, int x, int y) {
    if (!buffer || !buffer->data ||
        x < 0 || x >= buffer->cols ||
        y < 0 || y >= buffer->rows) {
        return ' ';
    }
    return buffer->data[y][x];
}

// set char
void set_pixel(Buffer* buffer, int x, int y, char ch) {
    if (!buffer || !buffer->data ||
        x < 0 || x >= buffer->cols ||
        y < 0 || y >= buffer->rows) {
        return;
    }
    buffer->data[y][x] = ch;
}
