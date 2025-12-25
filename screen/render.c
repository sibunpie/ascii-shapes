#include <stdio.h>
#include "render.h"

// clear terminal screen
void clear_screen(void) {
    printf("\033[2J\033[H");
    fflush(stdout);
}

// output buffer on the screen
void render(Buffer* buffer) {
    if (!buffer || !buffer->data) return;

    // move the cursor to the beginning
    printf("\033[H");

    for (int y = 0; y < buffer->rows; y++) {
        for (int x = 0; x < buffer->cols; x++) {
            putchar(buffer->data[y][x]);
        }
        if (y < buffer->rows - 1) {
            putchar('\n');
        }
    }
    fflush(stdout);
}
