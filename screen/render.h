#ifndef RENDER_H
#define RENDER_H

#include <sys/ioctl.h>
#include "../utils/buffer.h"

// render functions
void render(Buffer* buffer);
void clear_screen(void);

#endif // RENDER_H
