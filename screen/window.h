#ifndef WINDOW_H
#define WINDOW_H

#include <sys/ioctl.h>
#include <stdbool.h>

// functions for work with windows
bool get_console_size(struct winsize *w);

#endif // WINDOW_H
