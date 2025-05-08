# Compiler and compiler flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g # -g adds debugging symbols
LDFLAGS = # Add any linker flags if needed, e.g., -lm for math library

# Target executable name
TARGET = cyfighters

# Automatically find all .c files in the current directory
SRCS = $(wildcard *.c)

# Object files (derived from source files)
OBJS = $(SRCS:.c=.o)

# Header files (optional for this automatic setup, but good for explicit dependencies if needed)
# If you have headers in subdirectories, you might need to adjust include paths with -I
# For now, this Makefile assumes headers are in the same directory or standard include paths.

# Default target: build the executable
all: $(TARGET)

# Rule to link the executable
$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile .c files into .o files
# $< is the first prerequisite (the .c file)
# $@ is the target name (the .o file)
# The -MMD -MP flags generate dependency files (.d) which are then included.
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -MMD -MP

# Include dependency files if they exist
# This allows recompilation if a header file changes.
-include $(OBJS:.o=.d)

# Target to clean up build files
clean:
	rm -f $(OBJS) $(TARGET) $(OBJS:.o=.d)

# Phony targets (targets that don't represent actual files)
.PHONY: all clean