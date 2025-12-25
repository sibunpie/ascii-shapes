#ifndef DRAW_H
#define DRAW_H

#include <sys/ioctl.h>
#include "../utils/buffer.h"
#include "../utils/coord.h"

// draw functions
void draw_line(Buffer* buffer, Coord* coord, char ch);
void draw_rect(Buffer* buffer, Coord* coord, char ch);

#endif // DRAW_H
