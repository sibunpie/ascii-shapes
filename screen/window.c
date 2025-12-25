#include <stdio.h>
#include <unistd.h>
#include "window.h"

// terminal size get function
bool get_console_size(struct winsize *w) {
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, w) == -1) {
        perror("Failed to get console size");
        return false;
    }
    return true;
}
