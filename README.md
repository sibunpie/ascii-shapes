# ASCII Shapes

A lightweight C library for rendering lines and basic shapes in the terminal console using ASCII characters. The project provides a simple solution for terminal-based graphics.

## Features

- 📏 **Line Drawing**    - Bresenham's line algorithm implementation
- 📐 **Basic Shapes**    - Rectangles, frames, and custom patterns
- 🎨 **Terminal Buffer** - Double-buffered rendering to prevent flickering
- 📊 **Dynamic Sizing**  - Automatically adapts to terminal dimensions
- ⚡ **Real-time Input**  - Non-blocking keyboard input handling

## Project Structure

```
liner/
├── Makefile              # Build configuration
├── main.c                # Main application entry point
├── utils/
│   ├── coord.h           # Coordinate structures and functions
│   ├── coord.c
│   ├── buffer.h          # Screen buffer management
│   └── buffer.c
├── screen/
│   ├── window.h          # Terminal window operations
│   ├── window.c
│   ├── render.h          # Rendering functions
│   ├── render.c
│   ├── draw.h            # Drawing algorithms
│   └── draw.c
└── build                 # Object files for build
```

## Installation

### Prerequisites

- GCC compiler (or any C99 compatible compiler)
- Unix-like terminal (Linux, macOS, WSL) or Windows Terminal
- Make build system

### Building from Source

```bash
# Clone or download the project
git clone https://github.com/sibunpie/ascii-shapes
cd ascii-shapes/

# Build the project
make

# Run the application
./ascii_shapes
```

### Manual Compilation

```bash
gcc -Wall -Wextra -O2 \
    main.c \
    utils/coord.c \
    utils/buffer.c \
    screen/window.c \
    screen/render.c \
    screen/draw.c \
    -o ascii_shapes
```

## API Reference

### Core Components

#### Buffer Management
```c
// Create and initialize screen buffer
Buffer* create_buffer(struct winsize *w);

// Free buffer memory
void destroy_buffer(Buffer* buffer);

// Clear buffer (fill with spaces)
void clear_buffer(Buffer* buffer);

// Set/get individual pixels
void set_pixel(Buffer* buffer, int x, int y, char ch);
char get_pixel(Buffer* buffer, int x, int y);
```

#### Drawing Functions
```c
// Draw a line between two points
void draw_line(Buffer* buffer, Coord* coord, char ch);

// Draw a rectangle
void draw_rect(Buffer* buffer, Coord* coord, char ch);
```

#### Terminal Operations
```c
// Get terminal dimensions
bool get_console_size(struct winsize *w);

// Clear terminal screen
void clear_screen(void);

// Render buffer to terminal
void render(Buffer* buffer);
```

### Example Usage

```c
#include "screen/window.h"
#include "utils/buffer.h"
#include "screen/draw.h"

int main() {
    // Get terminal size
    struct winsize w;
    get_console_size(&w);

    // Create buffer
    Buffer* buffer = create_buffer(&w);

    // Draw a line from (10,5) to (50,20)
    Coord line, rect;
    set_coordinate(&w, &line, 10, 5, 50, 20);
    set_coordinate(&w, &rect, 40, 3, 65, 10);

    /*
    =============================================================================
    You can check if the coordinates are specified correctly. Return type: [bool]
    -----------------------------------------------------------------------------
    #include <stdio.h>
    #include <unistd.h>
    ...
    if (!set_coordinate(&w, &rect, 40, 3, 65, 10)) {
        perror("Incorrect coordinates\n");
        return EXIT_FAILURE;
    }
    =============================================================================
    */

    // Draw a line
    draw_line(buffer, &line, '#');

    // Draw a rectangle
    draw_rect(buffer, 5, 3, 30, 15, '@');

    // Render to screen
    render(buffer);

    // Cleanup
    destroy_buffer(buffer);

    return 0;
}
```

## Makefile Targets

- `make` or `make all` - Build the project
- `make clean` - Remove build artifacts
- `make run` - Build and run the application
- `make setup` - Create necessary directories

## Examples

### Basic Line Drawing
```c
// Draw multiple lines to create a pattern
for (int i = 0; i < 10; i++) {
    Coord line;
    set_coordinate(&w, &line, i*5, 2, i*5, 20);
    draw_line(buffer, &line, '/');
}
```


### Animated Rectangle
```c
// Simple animation loop
for (int frame = 0; frame < 100; frame++) {
    clear_buffer(buffer);
    draw_rect(buffer, frame%w.ws_col, 5, (frame%w.ws_col)+10, 15, '*');
    render(buffer);
    usleep(100000); // 10 FPS
}
```

### Interactive Drawing
```c
// Draw based on mouse/keyboard input
// (See input handling in the examples directory)
```

## Platform Support

### Linux
Full support. Uses `ioctl()` with `TIOCGWINSZ` to get terminal size.

### macOS
Full support. Compatible with Terminal and iTerm2.

### Windows
- **WSL (Windows Subsystem for Linux)**: Full support
- **Native Windows**: Requires additional implementation for terminal size detection

### Terminal Compatibility
- xterm, gnome-terminal, konsole
- iTerm2 (macOS)
- Windows Terminal
- Alacritty, kitty

## Performance Considerations

- **Double Buffering**: Prevents screen flickering during updates
- **Minimal Redraw**: Only updates changed pixels
- **Efficient Algorithms**: Uses integer-based Bresenham's algorithm
- **Memory Efficient**: Allocates only necessary buffer space

## Limitations

- ASCII characters only (limited graphical resolution)
- No built-in color support in current version
- Terminal resizing requires buffer reallocation
- Limited to 2D rendering

## Extending the Project

### Adding Colors
```c
// Extend the Buffer struct to include color information
typedef struct {
    char ch;
    int fg_color;  // Foreground color
    int bg_color;  // Background color
} Pixel;

// Update rendering to output ANSI color codes
```

### Adding More Shapes
```c
// Implement circle drawing
void draw_circle(Buffer* buffer, int center_x, int center_y, int radius, char ch);

// Implement triangle drawing
void draw_triangle(Buffer* buffer, int x1, int y1, int x2, int y2, int x3, int y3, char ch);
```

### Adding Input Handling
```c
// Non-blocking keyboard input
void enable_raw_mode(void);
char get_input(void);
void disable_raw_mode(void);
```

## Troubleshooting

### Common Issues

1. **Terminal doesn't clear properly**
   ```bash
   # Ensure your terminal supports ANSI escape codes
   echo $TERM
   ```

2. **Screen flickering**
   ```c
   // Enable double buffering in your main loop
   Buffer* front_buffer = create_buffer(&w);
   Buffer* back_buffer = create_buffer(&w);
   // Draw to back_buffer, then swap
   ```

3. **Incorrect terminal size detection**
   ```c
   // Fallback to default size
   if (!get_console_size(&w)) {
       w.ws_row = 24;
       w.ws_col = 80;
   }
   ```

### Debug Mode
Compile with debug flags:
```bash
make CFLAGS="-Wall -Wextra -g -DDEBUG"
```

## Contributing

1. Fork the repository
2. Create a feature branch
3. Implement your changes
4. Add tests if applicable
5. Submit a pull request

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

- Bresenham's line algorithm
- ANSI escape codes specification
- The ncurses library for inspiration

## Future Roadmap

- [ ] Add color support (256 colors and TrueColor)
- [ ] Implement anti-aliasing for smoother lines
- [ ] Add texture/fill patterns
- [ ] Support for Unicode box-drawing characters
- [ ] Mouse input handling
- [ ] Animation and transition effects
- [ ] Export frames to text files
- [ ] WebAssembly port for browser execution
- [ ] Add native support for Windows

## Support

For issues, questions, or feature requests:
1. Check the existing issues
2. Create a new issue with a detailed description
3. Include your platform and terminal information

---

**Note**: This is a lightweight educational project. For production terminal applications, consider using established libraries like ncurses or termbox. The project is being updated as the author learns. You can also contribute.
