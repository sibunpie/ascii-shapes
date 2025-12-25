#ifndef BUFFER_H
#define BUFFER_H

#include <sys/ioctl.h>

// structure for buffer
typedef struct {
    int rows;
    int cols;
    char** data; // two-dimensional array
} Buffer;

// functions
Buffer* create_buffer(struct winsize *w);
void destroy_buffer(Buffer* buffer);
void clear_buffer(Buffer* buffer);
char get_pixel(Buffer* buffer, int x, int y);
void set_pixel(Buffer* buffer, int x, int y, char ch);

#endif // BUFFER_H
