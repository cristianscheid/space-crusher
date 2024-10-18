# Compiler and flags
CC = gcc
CFLAGS = -g -Wall -Iinclude
LDFLAGS = -lSDL2 -lSDL2_image

# Source files and object files
SRCDIR = src
INCDIR = include
OBJDIR = build
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

# Executable name
TARGET = $(OBJDIR)/space-crusher

# Default rule
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Rule to compile .c files to .o files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) -c $(CFLAGS) $< -o $@

# Clean up object files and binary
clean:
	rm -rf $(OBJDIR)
