CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = ascii_shapes
BUILD_DIR = build

# Source files with correct paths
SRC_DIR = .
SOURCES = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/utils/coord.c \
	$(SRC_DIR)/utils/buffer.c \
	$(SRC_DIR)/screen/window.c \
	$(SRC_DIR)/screen/render.c \
	$(SRC_DIR)/screen/draw.c

OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

# Rule for compiling .c files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(SRC_DIR) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

run: $(TARGET)
	./$(TARGET)

setup:
	mkdir -p utils screen
	mkdir -p $(BUILD_DIR)/utils $(BUILD_DIR)/screen

# Force rebuild
rebuild: clean all

.PHONY: all clean run setup rebuild
