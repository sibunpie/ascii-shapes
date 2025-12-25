// main.c
#include <stdio.h>
#include <stdlib.h>

#include "utils/coord.h"
#include "utils/buffer.h"
#include "screen/window.h"
#include "screen/render.h"
#include "screen/draw.h"

int main(void) {
    // clear screen
    clear_screen();

    // getting console size
    struct winsize w;
    if (!get_console_size(&w)) {
        fprintf(stderr, "Failed to get console size\n");
        return EXIT_FAILURE;
    }
    w.ws_row -= 1; // for correct render

    printf("Console size: %dx%d\n", w.ws_row, w.ws_col);

    // create buffer
    Buffer* buffer = create_buffer(&w);
    if (!buffer) {
        fprintf(stderr, "Failed to create buffer\n");
        return EXIT_FAILURE;
    }

    // create coordinates for line & rectangle
    Coord line_coords, rect_coords;
    if (!set_coordinate(&w, &line_coords, 3, 3, 30, 15)) {
        fprintf(stderr, "Failed to set coordinates\n");
        destroy_buffer(buffer);
        return EXIT_FAILURE;
    } else if (!set_coordinate(&w, &rect_coords, 40, 3, 65, 10)) {
        fprintf(stderr, "Failed to set coordinates\n");
        destroy_buffer(buffer);
        return EXIT_FAILURE;
    }

    // lines
    draw_line(buffer, &line_coords, '#');
    if (!set_coordinate(&w, &line_coords, 65, 20, 100, 5)) {
        fprintf(stderr, "Failed to set coordinates\n");
        destroy_buffer(buffer);
        return EXIT_FAILURE;
    }
    draw_line(buffer, &line_coords, '#');

    // rectangles
    draw_rect(buffer, &rect_coords, '@');
    if (!set_coordinate(&w, &rect_coords, 0, 0, w.ws_col-1, w.ws_row-1)) {
        fprintf(stderr, "Failed to set coordinates\n");
        destroy_buffer(buffer);
        return EXIT_FAILURE;
    }
    draw_rect(buffer, &rect_coords, '*');   // frame

    // print text
    char* message = "LINER by sibunpie";
    int start_x = (w.ws_col - 17) / 2;
    for (int i = 0; message[i] != '\0'; i++) {
        if (start_x + i < w.ws_col && 2 < w.ws_row) {
            buffer->data[2][start_x + i] = message[i];
        }
    }

    render(buffer);

    printf("\nPress some key to exit...");
    getchar();

    destroy_buffer(buffer);

    return EXIT_SUCCESS;
}
